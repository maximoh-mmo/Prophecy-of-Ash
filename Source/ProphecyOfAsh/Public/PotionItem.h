#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "PotionItem.generated.h"

UENUM(BlueprintType)
enum class EPotionEffect : uint8
{
	//Placeholder stats
	Health      UMETA(DisplayName = "Health"),
	Mana        UMETA(DisplayName = "Mana"),
	Stamina     UMETA(DisplayName = "Stamina"),
	Strength    UMETA(DisplayName = "Strength"),
	Speed       UMETA(DisplayName = "Speed")
};

UCLASS(BlueprintType, Blueprintable)
class YOUR_API UPotionItem : public UItem
{
	GENERATED_BODY()

public:
	UPotionItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Potion")
	EPotionEffect PotionEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Potion")
	float EffectAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Potion")
	float EffectDuration;
	
	virtual bool CanUse_Implementation() const override;
	virtual bool Use_Implementation(AActor* User) override;
	virtual bool CanEquip_Implementation() const override;
};