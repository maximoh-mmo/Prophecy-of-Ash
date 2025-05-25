#include "POA_Item.h"

APOA_Item::APOA_Item()
{
	Name = TEXT("Default Item");
	Description = TEXT("An Item");
	Icon = nullptr;
	MaxStackCount = 1;
	Value = 1;
	ItemType = EItemType::Misc;
	CurrentStackCount = 1;
}


bool APOA_Item::CanStack_Implementation(const APOA_Item* OtherItem) const
{
	return OtherItem && 
		   GetClass() == OtherItem->GetClass() && 
		   Name == OtherItem->Name && 
		   MaxStackCount > 1;
}


bool APOA_Item::CanUse_Implementation() const
{

	return false;
}

bool APOA_Item::CanEquip_Implementation() const
{

	return false;
}

bool APOA_Item::Use_Implementation(AActor* User)
{

	return false;
}

bool APOA_Item::Equip_Implementation(AActor* Actor)
{
	return false;
}


bool APOA_Item::UnEquip_Implementation(AActor* Actor)
{
	return false;
}

void APOA_Item::AddToStack(int32 Amount)
{
	if (Amount <= 0) return;
    
	CurrentStackCount = FMath::Min(CurrentStackCount + Amount, MaxStackCount);
}

bool APOA_Item::RemoveFromStack(int32 Amount)
{
	if (Amount <= 0) return true;
    
	if (CurrentStackCount >= Amount)
	{
		CurrentStackCount -= Amount;
		return true;
	}
    
	return false;
}

FString APOA_Item::GetItemID() const
{
	// This creates an ID based on name and class of item
	return FString::Printf(TEXT("%s_%s"), *GetClass()->GetName(), *Name);
}