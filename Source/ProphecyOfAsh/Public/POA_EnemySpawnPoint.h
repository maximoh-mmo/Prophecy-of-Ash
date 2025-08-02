// Fill out your copyright notice in the Description page of Project Settings.

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
	int32 NumberToSpawn = 0;
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

protected:
	virtual void BeginPlay() override;
};
