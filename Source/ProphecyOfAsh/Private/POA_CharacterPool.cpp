// Fill out your copyright notice in the Description page of Project Settings.


#include "POA_CharacterPool.h"

#include "Components/CapsuleComponent.h"

// Sets default values for this component's properties

UPOA_CharacterPool::UPOA_CharacterPool()
{
}

APOA_PooledCharacter* UPOA_CharacterPool::TakeFromPool(FVector Location = FVector().Zero(), FRotator Rotation = FRotator().ZeroRotator)
{
	for (APOA_PooledCharacter* Character : CharacterPool)
	{
		if (Character && !Character->IsActive())
		{
			Location += Character->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() * FVector(0, 0, 1);
			Character->TeleportTo(Location, Rotation, false, true);
			Character->SetActive(true);
			SpawnedCharacterIndices.Add(Character->GetPoolIndex());
			return Character;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("No available characters in pool, extending pool..."));
	ExtendPool();
	return TakeFromPool(Location, Rotation);
}

void UPOA_CharacterPool::SetPoolClass(TSubclassOf<APOA_PooledCharacter> NewPooledCharacterClass)
{
	UE_LOG(LogTemp, Warning, TEXT("Setting new PooledCharacterClass: %s"), *NewPooledCharacterClass->GetName());
	PooledCharacterClass = NewPooledCharacterClass;
	if (CharacterPool.Num() != 0)
	{
		for (APOA_PooledCharacter* Character : CharacterPool)
		{
			if (Character)
			{
				Character->SetActive(false);
				Character->Destroy();
			}
		}
		CharacterPool.Empty();
		SpawnedCharacterIndices.Empty();
	}
	ExtendPool();
}


void UPOA_CharacterPool::OnPooledCharacterDespawn(APOA_PooledCharacter* PoolActor)
{
	SpawnedCharacterIndices.Remove(PoolActor->GetPoolIndex());
}

void UPOA_CharacterPool::ExtendPool()
{
	if (Extending)
	{
		UE_LOG(LogTemp, Warning, TEXT("Already extending pool, skipping..."));
		return;
	}
	Extending = true;
	if (PoolSize == CharacterPool.Num())
	{
		PoolSize += DefaultPoolSize;
	}
	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("UPOA_CharacterPool::BeginPlay: World is null!"));
		return;
	}

	while (CharacterPool.Num() < PoolSize)
	{
		if (PooledCharacterClass)
		{
			APOA_PooledCharacter* NewCharacter = World->SpawnActor<APOA_PooledCharacter>(PooledCharacterClass,
				FVector().Zero(), FRotator().ZeroRotator);

			if (NewCharacter)
			{
				NewCharacter->SetActive(false);
				NewCharacter->OnPooledCharacterDespawn.AddDynamic(this, &UPOA_CharacterPool::OnPooledCharacterDespawn);
				NewCharacter->SetPoolIndex(CharacterPool.Num());
				CharacterPool.Add(NewCharacter);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Failed to spawn Pooled Character!"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("PooledCharacterClass is not set!"));
		}
	}
	Extending = false;
}

// Called when the game starts
void UPOA_CharacterPool::BeginPlay()
{
	Super::BeginPlay();
	if (PoolSize <= 0)
	{
		PoolSize = DefaultPoolSize;
	}
	if (PooledCharacterClass == nullptr)
		return;
	ExtendPool();
}

