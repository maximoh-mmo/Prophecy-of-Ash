//
// Copyright 2025 Max Heinze. All Rights Reserved.
//
// This file is part of the Prophecy of Ash project.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class PROPHECYOFASH_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

	UFUNCTION(BlueprintCallable, Category = "Enemy Spawner")
	void EnemyKilled(AActor* DeadEnemy);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool SpawnEnemy();
	bool ReSpawnEnemy(AActor* Enemy);

	bool SpawnEnemy(AActor* Enemy);

	void RespawnEnemy();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Spawner")
	TSubclassOf<AActor> EnemyClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Spawner")
	float RespawnTimer = 5.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Spawner")
	int NumberToSpawn = 2;

	TArray<AActor*> AliveEnemies;
	TArray<AActor*> AwaitingRespawn;
	TArray<FTimerHandle> RespawnTimers;
};
