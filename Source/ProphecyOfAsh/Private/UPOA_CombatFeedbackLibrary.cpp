// Fill out your copyright notice in the Description page of Project Settings.


#include "UPOA_CombatFeedbackLibrary.h"
#include "POA_CombatFeedbackSubsystem.h"
#include "Engine/World.h"


void UUPOA_CombatFeedbackLibrary::TriggerFeedbackFromCue(UObject* WorldContextObject, FGameplayTag FeedbackTag, AActor* Instigator, AActor* Target)
{
	if (UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		if (UPOA_CombatFeedbackSubsystem* Subsystem = World->GetSubsystem<UPOA_CombatFeedbackSubsystem>())
		{
			Subsystem->TriggerFeedback(FeedbackTag, Instigator, Target);
		}
	}
}
