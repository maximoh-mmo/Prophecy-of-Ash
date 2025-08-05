// Fill out your copyright notice in the Description page of Project Settings.

#include "POA_PlayerCharacter.h"

#include "POA_EnemySpawnPoint.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "SkeletalMeshComponentBudgeted.h"


DEFINE_LOG_CATEGORY(LogEnemyPool);

void APOA_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	RetargetedMesh = CreateDefaultSubobject<USkeletalMeshComponentBudgeted>(TEXT("RetargetedMesh"));
	RetargetedMesh->SetupAttachment(GetMesh());
	RetargetedMesh->SetAutoRegisterWithBudgetAllocator(true);
	RetargetedMesh->SetAutoCalculateSignificance(true);

	TArray<AActor*> SpawnPoints;
	TArray<FVector> SpawnLocations;
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (!NavSystem) return;
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), TSubclassOf<APOA_EnemySpawnPoint>(), SpawnPoints);
	for (auto SpawnPoint : SpawnPoints)
	{
		auto SP = Cast<APOA_EnemySpawnPoint>(SpawnPoint);
		FVector SPLoc =	SP->GetActorTransform().GetLocation();
		auto enemyClass = SP->EnemySpawnDetail.EnemyClass;
		for (int i = 0; i < SP->NumberToSpawn; ++i)
		{
			FNavLocation NavLocation;
			for (int j = 0; j < 10; ++j)
			{
				if (NavSystem->GetRandomPointInNavigableRadius(SPLoc, SP->SpawnRadius, NavLocation))
				{
					SpawnLocations.Add(NavLocation.Location);
					UE_LOG(LogEnemyPool, Log, TEXT("Added %s"), *NavLocation.Location.ToCompactString() )
					break;
				}
			}
		}
	}
}
