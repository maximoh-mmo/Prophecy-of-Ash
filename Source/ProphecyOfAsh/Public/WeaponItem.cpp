#include "WeaponItem.h"

AWeaponItem::AWeaponItem()
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

bool AWeaponItem::CanUse_Implementation() const
{
	return false;
}

bool AWeaponItem::CanEquip_Implementation() const
{
	return true; 
}

bool AWeaponItem::Equip_Implementation(AActor* Actor)
{
	if (!Actor) return false;
	
	// Debug text, should spawn weapon instead
    
	UE_LOG(LogTemp, Display, TEXT("Weapon %s equipped by %s"), *Name, *Actor->GetName());
    
	bIsEquipped = true;
	return true;
}

bool AWeaponItem::UnEquip_Implementation(AActor* Actor)
{
	if (!Actor) return false;
	
    //Debug text, should destroy weapon actor on unequip instead
	UE_LOG(LogTemp, Display, TEXT("Weapon %s unequipped by %s"), *Name, *Actor->GetName());
    
	bIsEquipped = false;
	return true;
}
