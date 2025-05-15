#include "Inventory.h"
#include "Item.h"

UInventory::UInventory()
{
    PrimaryComponentTick.bCanEverTick = false;
    
    MaxSlots = 20;
}

void UInventory::BeginPlay()
{
    Super::BeginPlay();
    
    Slots.SetNum(MaxSlots);
}


void UInventory::NotifyItemAdded(UItem* Item)
{
    if (!Item) return;
    
    OnItemAdded.Broadcast(this, Item);
}

void UInventory::NotifyItemRemoved(UItem* Item)
{
    if (!Item) return;
    
    OnItemRemoved.Broadcast(this, Item);
}

void UInventory::NotifyItemUsed(UItem* Item)
{
    if (!Item) return;
    
    OnItemUsed.Broadcast(this, Item);
}

void UInventory::NotifyItemEquipped(UItem* Item)
{
    if (!Item) return;
    
    OnItemEquipped.Broadcast(this, Item);
}

void UInventory::NotifyItemUnequipped(UItem* Item)
{
    if (!Item) return;
    
    OnItemUnequipped.Broadcast(this, Item);
}

bool UInventory::AddItem(UItem* Item, int32 Quantity)
{
    if (!Item || Quantity <= 0)
    {
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
        

        UItem* NewItem = NewObject<UItem>(this, Item->GetClass());
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

bool UInventory::RemoveItem(UItem* Item, int32 Quantity)
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

bool UInventory::UseItem(UItem* Item)
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

bool UInventory::EquipItem(UItem* Item)
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

bool UInventory::UnequipItem(UItem* Item)
{
    if (!Item)
    {
        return false;
    }
    

    if (!EquippedItems.Contains(Item))
    {
        return false;
    }
    

    AActor* Owner = GetOwner();
    if (Item->Unequip(Owner))
    {

        EquippedItems.Remove(Item);
        

        NotifyItemUnequipped(Item);
        
        return true;
    }
    
    return false;
}


int32 UInventory::GetItemCount(UItem* ItemTemplate) const
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

TArray<UItem*> UInventory::GetItemsByType(EItemType Type) const
{
    TArray<UItem*> Result;
    
    for (const auto& Slot : Slots)
    {
        if (Slot.Item && Slot.Item->ItemType == Type)
        {
            Result.Add(Slot.Item);
        }
    }
    
    return Result;
}

bool UInventory::HasItem(UItem* ItemTemplate, int32 Quantity) const
{
    return GetItemCount(ItemTemplate) >= Quantity;
}

bool UInventory::IsItemEquipped(UItem* Item) const
{
    return EquippedItems.Contains(Item);
}