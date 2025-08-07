// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "CombatFeedbackDataAsset.h"
#include "Components/ActorComponent.h"
#include "CombatFeedbackComponent.generated.h"


UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROPHECYOFASH_API UCombatFeedbackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCombatFeedbackComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat Feedback")
	UCombatFeedbackDataAsset* FeedbackDataAsset;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent,Category = "Combat Feedback")
	void HandleFeedback_BP(const FGameplayTag FeedbackTag, AActor* InstigatorActor, AActor* TargetActor);

		
};
