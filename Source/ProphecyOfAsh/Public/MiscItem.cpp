#include "MiscItem.h"

UMiscItem::UMiscItem()
{
	Name = TEXT("Misc Item");
	Description = TEXT("A miscellaneous item");
	ItemType = EItemType::Misc;
	MaxStackCount = 99;  
}

bool UMiscItem::CanUse_Implementation() const
{
	return false; 
}

bool UMiscItem::CanEquip_Implementation() const
{
	return false;  
}