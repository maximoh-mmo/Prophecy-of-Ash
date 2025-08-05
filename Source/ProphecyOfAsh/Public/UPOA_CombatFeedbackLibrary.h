// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UPOA_CombatFeedbackLibrary.generated.h"

/**
 * 
 */
UCLASS()
class PROPHECYOFASH_API UUPOA_CombatFeedbackLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/** Triggers feedback through the subsystem using GameplayTag. Usable in Gameplay Cues or abilities. */
	UFUNCTION(BlueprintCallable, Category = "Combat Feedback", meta = (WorldContext = "WorldContextObject"))
	static void TriggerFeedbackFromCue(UObject* WorldContextObject, FGameplayTag FeedbackTag, AActor* Instigator, AActor* Target);

};
