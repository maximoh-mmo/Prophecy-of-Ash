#include "POA_Inventory.h"
#include "POA_Item.h"

UPOA_Inventory::UPOA_Inventory()
{
    PrimaryComponentTick.bCanEverTick = false;
    
    MaxSlots = 20;
}

void UPOA_Inventory::BeginPlay()
{
    Super::BeginPlay();
    
    Slots.SetNum(MaxSlots);
}


void UPOA_Inventory::NotifyItemAdded(APOA_Item* Item)
{
    UE_LOG(LogTemp, Warning, TEXT("Attempt to notify Item added."));
    if (!Item) {
        UE_LOG(LogTemp, Warning, TEXT("Item Invalid"));
        return;
    }
    OnItemAdded.Broadcast(this, Item);
    UE_LOG(LogTemp, Warning, TEXT("Item added event called"))
}

void UPOA_Inventory::NotifyItemRemoved(APOA_Item* Item)
{
    if (!Item) return;
    
    OnItemRemoved.Broadcast(this, Item);
}

void UPOA_Inventory::NotifyItemUsed(APOA_Item* Item)
{
    if (!Item) return;
    
    OnItemUsed.Broadcast(this, Item);
}

void UPOA_Inventory::NotifyItemEquipped(APOA_Item* Item)
{
    if (!Item) return;
    
    OnItemEquipped.Broadcast(this, Item);
}

void UPOA_Inventory::NotifyItemUnequipped(APOA_Item* Item)
{
    if (!Item) return;
    
    OnItemUnequipped.Broadcast(this, Item);
}

bool UPOA_Inventory::AddItem(APOA_Item* Item, int32 Quantity)
{
    UE_LOG(LogTemp, Warning, TEXT("Attempt to add item"));

    if (!Item || Quantity <= 0)
    {
        UE_LOG(LogTemp, Error, TEXT("Item not valid"));

        return false;
    }
   
    for (auto& Slot : Slots)
    {
        if (Slot.Item && Slot.Item->CanStack(Item))
        {
            int32 CanAdd = FMath::Min(Quantity, Slot.Item->MaxStackCount - Slot.Quantity);
            if (CanAdd > 0)
            {
                Slot.Quantity += CanAdd;
                Quantity -= CanAdd;

                NotifyItemAdded(Item);
                         
                if (Quantity <= 0)
                {
                    return true;
                }
            }
        }
    }
    

    while (Quantity > 0)
    {

        int32 EmptySlotIndex = INDEX_NONE;
        for (int32 i = 0; i < Slots.Num(); i++)
        {
            if (!Slots[i].Item)
            {
                EmptySlotIndex = i;
                break;
            }
        }
        

        if (EmptySlotIndex == INDEX_NONE)
        {
            UE_LOG(LogTemp, Warning, TEXT("Cannot add item %s: inventory is full"), *Item->Name);
            return false;
        }
        

        APOA_Item* NewItem = NewObject<APOA_Item>(this, Item->GetClass());
        if (!NewItem)
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to create new instance of item %s"), *Item->GetClass()->GetName());
            return false;
        }
        
     
        NewItem->Name = Item->Name;
        NewItem->Description = Item->Description;
        NewItem->Icon = Item->Icon;
        NewItem->MaxStackCount = Item->MaxStackCount;
        NewItem->Value = Item->Value;
        NewItem->ItemType = Item->ItemType;
        
    
        int32 ToAdd = FMath::Min(Quantity, NewItem->MaxStackCount);
        Slots[EmptySlotIndex].Item = NewItem;
        Slots[EmptySlotIndex].Quantity = ToAdd;
        
    
        Quantity -= ToAdd;
        

        NotifyItemAdded(NewItem);
    }
    
    return true;
}

bool UPOA_Inventory::RemoveItem(APOA_Item* Item, int32 Quantity)
{
    if (!Item || Quantity <= 0)
    {
        return false;
    }
    
    int32 RemainingToRemove = Quantity;
    
 
    for (auto& Slot : Slots)
    {
        if (Slot.Item && Slot.Item->GetItemID() == Item->GetItemID())
        {
            int32 ToRemove = FMath::Min(RemainingToRemove, Slot.Quantity);
            Slot.Quantity -= ToRemove;
            RemainingToRemove -= ToRemove;
            
           
            if (Slot.Quantity <= 0)
            {
             
                NotifyItemRemoved(Slot.Item);
                Slot.Item = nullptr;
                Slot.Quantity = 0;
            }
            else
            {
                
                NotifyItemRemoved(Item);
            }
            
           
            if (RemainingToRemove <= 0)
            {
                return true;
            }
        }
    }
    

    return RemainingToRemove == 0;
}

bool UPOA_Inventory::UseItem(APOA_Item* Item)
{
    if (!Item || !Item->CanUse())
    {
        return false;
    }
    

    for (auto& Slot : Slots)
    {
        if (Slot.Item && Slot.Item == Item && Slot.Quantity > 0)
        {
           
            AActor* Owner = GetOwner();
            if (Item->Use(Owner))
            {
               
                NotifyItemUsed(Item);
                
              
                if (Item->ItemType == EItemType::Potion)
                {
                    Slot.Quantity--;
                    
                  
                    if (Slot.Quantity <= 0)
                    {
                        NotifyItemRemoved(Slot.Item);
                        Slot.Item = nullptr;
                        Slot.Quantity = 0;
                    }
                }
                
                return true;
            }
        }
    }
    
    return false;
}

bool UPOA_Inventory::EquipItem(APOA_Item* Item)
{
    if (!Item || !Item->CanEquip())
    {
        return false;
    }
    
   
    bool bFoundInInventory = false;
    for (auto& Slot : Slots)
    {
        if (Slot.Item && Slot.Item == Item && Slot.Quantity > 0)
        {
            bFoundInInventory = true;
            break;
        }
    }
    
    if (!bFoundInInventory)
    {
        return false;
    }
    
  
    AActor* Owner = GetOwner();
    if (Item->Equip(Owner))
    {
        
        EquippedItems.AddUnique(Item);
        
     
        NotifyItemEquipped(Item);
        
        return true;
    }
    
    return false;
}

bool UPOA_Inventory::UnequipItem(APOA_Item* Item)
{
    if (!Item)
    {
        return false;
    }
    

    if (!EquippedItems.Contains(Item))
    {
        return false;
    }
    

    AActor* Actor = GetOwner();
    if (Item->UnEquip(Actor))
    {

        EquippedItems.Remove(Item);
        

        NotifyItemUnequipped(Item);
        
        return true;
    }
    
    return false;
}


int32 UPOA_Inventory::GetItemCount(APOA_Item* ItemTemplate) const
{
    if (!ItemTemplate)
    {
        return 0;
    }
    
    int32 Count = 0;
    
    for (const auto& Slot : Slots)
    {
        if (Slot.Item && Slot.Item->GetItemID() == ItemTemplate->GetItemID())
        {
            Count += Slot.Quantity;
        }
    }
    
    return Count;
}

TArray<APOA_Item*> UPOA_Inventory::GetItemsByType(EItemType Type) const
{
    TArray<APOA_Item*> Result;
    
    for (const auto& Slot : Slots)
    {
        if (Slot.Item && Slot.Item->ItemType == Type)
        {
            Result.Add(Slot.Item);
        }
    }
    
    return Result;
}

bool UPOA_Inventory::HasItem(APOA_Item* ItemTemplate, int32 Quantity) const
{
    return GetItemCount(ItemTemplate) >= Quantity;
}

bool UPOA_Inventory::IsItemEquipped(APOA_Item* Item) const
{
    return EquippedItems.Contains(Item);
}