#include "PotionItem.h"

UPotionItem::UPotionItem()
{
	Name = TEXT("Default Potion");
	Description = TEXT("A Potion");
	ItemType = EItemType::Potion;
	MaxStackCount = 10;  
    
	PotionEffect = EPotionEffect::Health;
	EffectAmount = 10.0f;
	EffectDuration = 0.0f;  
}

bool UPotionItem::CanUse_Implementation() const
{
	return true;  
}

bool UPotionItem::CanEquip_Implementation() const
{
	return false;  
}

bool UPotionItem::Use_Implementation(AActor* User)
{
	if (!User) return false;
    
	UE_LOG(LogTemp, Display, TEXT("Potion %s used by %s. Effect: %s, Amount: %f"),
		   *Name, *User->GetName(), *UEnum::GetValueAsString(PotionEffect), EffectAmount);
    

	return true;
}