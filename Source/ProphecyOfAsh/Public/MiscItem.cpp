#include "MiscItem.h"

AMiscItem::AMiscItem()
{
	Name = TEXT("Misc Item");
	Description = TEXT("A miscellaneous item");
	ItemType = EItemType::Misc;
	MaxStackCount = 99;  
}

bool AMiscItem::CanUse_Implementation() const
{
	return false; 
}

bool AMiscItem::CanEquip_Implementation() const
{
	return false;  
}