//
// Copyright 2025 Max Heinze. All Rights Reserved.
//
// This file is part of the Prophecy of Ash project.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "POA_EnemySpawnPoint.generated.h"

class APOA_PooledCharacter;

USTRUCT(Blueprintable)
struct FEnemySpawnDetail
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APOA_PooledCharacter> EnemyClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> EnemyKillObjectiveIDs;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int> LootTableIDs;
};

UCLASS()
class PROPHECYOFASH_API APOA_EnemySpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	APOA_EnemySpawnPoint();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Spawn Point")
	FEnemySpawnDetail EnemySpawnDetail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Spawn Point")
	int32 NumberToSpawn = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Spawn Point")
	float SpawnRadius = 10.0f; 

protected:
	virtual void BeginPlay() override;
};
