//
// Copyright 2025 Max Heinze. All Rights Reserved.
//
// This file is part of the Prophecy of Ash project.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "PatrolPoint.generated.h"

UCLASS()
class PROPHECYOFASH_API APatrolPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APatrolPoint();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Patrol Point")
	UStaticMeshComponent* MeshComponent;
	UPROPERTY(BlueprintReadWrite, Category = "Patrol Point")
	TArray<UArrowComponent*> FwdArrowComponents;
	UPROPERTY(BlueprintReadWrite, Category = "Patrol Point")
	TArray<UArrowComponent*> RevArrowComponents;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Patrol Point")
	TArray<APatrolPoint*> NextPatrolPoints;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Patrol Point")
	TArray<APatrolPoint*> PreviousPatrolPoints;
};
