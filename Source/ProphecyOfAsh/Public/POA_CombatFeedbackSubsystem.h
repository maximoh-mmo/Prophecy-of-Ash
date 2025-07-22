// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Subsystems/Subsystem.h"
#include "POA_CombatFeedbackSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class PROPHECYOFASH_API UPOA_CombatFeedbackSubsystem : public USubsystem
{
	GENERATED_BODY()

public:
	
	/** Trigger a feedback event based on GameplayTag */
	UFUNCTION(BlueprintCallable, Category = "Combat Feedback")
	void TriggerFeedback(const FGameplayTag FeedbackTag, AActor* InstigatorActor, AActor* TargetActor);

protected:

	/** Implement this in Blueprint to drive VFX, SFX, CamShake, etc. */
	UFUNCTION(BlueprintImplementableEvent, Category = "Combat Feedback")
	void HandleFeedback_BP(const FGameplayTag FeedbackTag, AActor* InstigatorActor, AActor* TargetActor);
};
