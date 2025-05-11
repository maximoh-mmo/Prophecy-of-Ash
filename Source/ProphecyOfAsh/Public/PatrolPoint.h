//
// Copyright 2025 Max Heinze. All Rights Reserved.
//
// This file is part of the Prophecy of Ash project.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PatrolPoint.generated.h"

UCLASS()
class PROPHECYOFASH_API APatrolPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APatrolPoint();

	UFUNCTION(BlueprintCallable, Category = "Patrol Point")
	void AddNextPoint(APatrolPoint* NextPoint);
	UFUNCTION(BlueprintCallable, Category = "Patrol Point")
	void AddPreviousPoint(APatrolPoint* PreviousPoint);
	UFUNCTION(BlueprintCallable, Category = "Patrol Point")
	void RemovePoint();

	void RemovePreviousPoint(APatrolPoint* PointToRemove);
	void RemoveNextPoint(APatrolPoint* PointToRemove);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Patrol Point")
	UStaticMeshComponent* MeshComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol Point")
	TArray <APatrolPoint*> NextPatrolPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol Point")
	TArray<APatrolPoint*> PreviousPatrolPoints;
};
