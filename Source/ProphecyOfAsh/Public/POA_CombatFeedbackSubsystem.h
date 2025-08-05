// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "CombatFeedbackDataAsset.h"
#include "Subsystems/WorldSubsystem.h"
#include "POA_CombatFeedbackSubsystem.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class PROPHECYOFASH_API UPOA_CombatFeedbackSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	
	/** Trigger a feedback event based on GameplayTag */
	UFUNCTION(BlueprintCallable, Category = "Combat Feedback")
	void TriggerFeedback(const FGameplayTag FeedbackTag, AActor* InstigatorActor, AActor* TargetActor);

	UFUNCTION(BlueprintCallable, Category = "Combat Feedback")
	void TriggerFeedbackMultiple(const FGameplayTag FeedbackTag, AActor* InstigatorActor, const TArray<AActor*>& TargetActors);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat Feedback")
	UCombatFeedbackDataAsset* FeedbackDataAsset;

protected:

	/** Implement this in Blueprint to drive VFX, SFX, CamShake, etc. */
	UFUNCTION(BlueprintImplementableEvent, Category = "Combat Feedback")
	void HandleFeedback_BP(const FGameplayTag FeedbackTag, AActor* InstigatorActor, AActor* TargetActor);
};
