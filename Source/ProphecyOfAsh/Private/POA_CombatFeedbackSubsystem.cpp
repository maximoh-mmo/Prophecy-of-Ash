// Fill out your copyright notice in the Description page of Project Settings.


#include "POA_CombatFeedbackSubsystem.h"

void UPOA_CombatFeedbackSubsystem::TriggerFeedback(const FGameplayTag FeedbackTag, AActor* InstigatorActor, AActor* TargetActor)
{
	UE_LOG(LogTemp, Log, TEXT("TriggerFeedback: %s | Instigator: %s | Target: %s"),
		*FeedbackTag.ToString(),
		*GetNameSafe(InstigatorActor),
		*GetNameSafe(TargetActor));
	HandleFeedback_BP(FeedbackTag, InstigatorActor, TargetActor);
}

void UPOA_CombatFeedbackSubsystem::TriggerFeedbackMultiple(const FGameplayTag FeedbackTag, AActor* InstigatorActor, const TArray<AActor*>& TargetActors)
{
	for (AActor* Target : TargetActors)
	{
		if (IsValid(Target))
		{
			TriggerFeedback(FeedbackTag, InstigatorActor, Target);
		}
	}
}
