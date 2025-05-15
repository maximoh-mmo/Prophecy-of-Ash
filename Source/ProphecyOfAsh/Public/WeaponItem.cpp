#include "WeaponItem.h"

UWeaponItem::UWeaponItem()
{
	Name = TEXT("Default Weapon");
	Description = TEXT("A weapon");
	ItemType = EItemType::Weapon;
	MaxStackCount = 1; 
    
	WeaponType = EWeaponType::Sword;
	Damage = 10.0f;
	AttackSpeed = 1.0f;
	WeaponActorClass = nullptr;
	bIsEquipped = false;
}

bool UWeaponItem::CanUse_Implementation() const
{
	return false;
}

bool UWeaponItem::CanEquip_Implementation() const
{
	return true; 
}

bool UWeaponItem::Equip_Implementation(AActor* Owner)
{
	if (!Owner) return false;
	
	// Debug text, should spawn weapon instead
    
	UE_LOG(LogTemp, Display, TEXT("Weapon %s equipped by %s"), *Name, *Owner->GetName());
    
	bIsEquipped = true;
	return true;
}

bool UWeaponItem::Unequip_Implementation(AActor* Owner)
{
	if (!Owner) return false;
	
    //Debug text, should destroy weapon actor on unequip instead
	UE_LOG(LogTemp, Display, TEXT("Weapon %s unequipped by %s"), *Name, *Owner->GetName());
    
	bIsEquipped = false;
	return true;
}
