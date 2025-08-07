#pragma once

#include "CoreMinimal.h"
#include "FMODEvent.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "NiagaraSystem.h"
#include "Camera/CameraShakeBase.h"
#include "CombatFeedbackDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FCombatFeedbackEffect
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UNiagaraSystem* VFX = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundBase* SFX = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UFMODEvent* FMOD_SFX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UCameraShakeBase> CameraShake;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString MaterialEffectParameter = "NONE";
};

UCLASS(BlueprintType)
class PROPHECYOFASH_API UCombatFeedbackDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FGameplayTag, FCombatFeedbackEffect> FeedbackMap;
};