#include "Item.h"

UItem::UItem()
{
	Name = TEXT("Default Item");
	Description = TEXT("An Item");
	Icon = nullptr;
	MaxStackCount = 1;
	Value = 1;
	ItemType = EItemType::Misc;
	CurrentStackCount = 1;
}


bool UItem::CanStack_Implementation(const UItem* OtherItem) const
{

	return OtherItem && 
		   GetClass() == OtherItem->GetClass() && 
		   Name == OtherItem->Name && 
		   MaxStackCount > 1;
}


bool UItem::CanUse_Implementation() const
{

	return false;
}

bool UItem::CanEquip_Implementation() const
{

	return false;
}

bool UItem::Use_Implementation(AActor* User)
{

	return false;
}

bool UItem::Equip_Implementation(AActor* Owner)
{

	return false;
}

bool UItem::Unequip_Implementation(AActor* Owner)
{

	return false;
}

void UItem::AddToStack(int32 Amount)
{
	if (Amount <= 0) return;
    
	CurrentStackCount = FMath::Min(CurrentStackCount + Amount, MaxStackCount);
}

bool UItem::RemoveFromStack(int32 Amount)
{
	if (Amount <= 0) return true;
    
	if (CurrentStackCount >= Amount)
	{
		CurrentStackCount -= Amount;
		return true;
	}
    
	return false;
}

FString UItem::GetItemID() const
{
	// This creates an ID based on name and class of item
	return FString::Printf(TEXT("%s_%s"), *GetClass()->GetName(), *Name);
}