// Fill out your copyright notice in the Description page of Project Settings.


#include "POA_CombatFeedbackSubsystem.h"

void UPOA_CombatFeedbackSubsystem::TriggerFeedback(const FGameplayTag FeedbackTag, AActor* InstigatorActor, AActor* TargetActor)
{
	HandleFeedback_BP(FeedbackTag, InstigatorActor, TargetActor);
}