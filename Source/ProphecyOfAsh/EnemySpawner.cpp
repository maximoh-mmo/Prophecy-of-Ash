// Fill out your copyright notice in the Description page of Project Settings.
#include "EnemySpawner.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemySpawner::EnemyKilled(AActor* DeadEnemy)
{
	// Remove the enemy from the AliveEnemies array
	AliveEnemies.Remove(DeadEnemy);
	// Add the enemy to the AwaitingRespawn array
	AwaitingRespawn.Add(DeadEnemy);
	// Start a timer to respawn the enemy
	GetWorld()->GetTimerManager().SetTimer(RespawnTimers[AwaitingRespawn.Num() - 1], [this, DeadEnemy]() {
		{
			RespawnEnemy();
		};
		}, RespawnTimer, false);
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < NumberToSpawn; i++)
	{
		if (SpawnEnemy())
		{
			
		};
	}
}

bool AEnemySpawner::SpawnEnemy()
{
	if (EnemyClass)
	{
		FVector SpawnLocation = GetActorLocation();
		float Yaw = FMath::FRandRange(-180.0f, 180.0f);
		FRotator SpawnRotation = FRotator(0.0f, Yaw, 0.0f);
		AActor* NewEnemy = GetWorld()->SpawnActor<AActor>(EnemyClass, SpawnLocation, SpawnRotation);
		if (NewEnemy)
		{
			AliveEnemies.Add(NewEnemy);
			return true;
		}
	}
	return false;
}

bool AEnemySpawner::ReSpawnEnemy(AActor* Enemy)
{
	FVector SpawnLocation = GetActorLocation();
	float Yaw = FMath::FRandRange(-180.0f, 180.0f);
	FRotator SpawnRotation = FRotator(0.0f, Yaw, 0.0f);
	return false;
	
}

void AEnemySpawner::RespawnEnemy()
{
	if (AwaitingRespawn.Num() > 0)
	{
		AActor* EnemyToRespawn = AwaitingRespawn[0];
		// Remove the enemy from the AwaitingRespawn array
		AwaitingRespawn.RemoveAt(0);
		// Add the enemy to the AliveEnemies array
		AliveEnemies.Add(EnemyToRespawn);
		ReSpawnEnemy(EnemyToRespawn);
	}
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

