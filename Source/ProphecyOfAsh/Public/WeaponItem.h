#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "WeaponItem.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	//Placehold weapon types
	Sword       UMETA(DisplayName = "Sword"),
	Axe         UMETA(DisplayName = "Axe"),
	Bow         UMETA(DisplayName = "Bow"),
	Staff       UMETA(DisplayName = "Staff"),
	Dagger      UMETA(DisplayName = "Dagger")
};

UCLASS(BlueprintType, Blueprintable)
class YOUR_API UWeaponItem : public UItem
{
	GENERATED_BODY()

public:
	UWeaponItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	EWeaponType WeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AActor> WeaponActorClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	bool bIsEquipped;


	virtual bool CanUse_Implementation() const override;
	virtual bool CanEquip_Implementation() const override;
	virtual bool Equip_Implementation(AActor* Owner) override;
	virtual bool Unequip_Implementation(AActor* Owner) override;
};