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
	if (CharacterPool.Num() == SpawnedCharacterIndices.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("No available characters in pool, extending pool..."));
		ExtendPool(DefaultPoolSize);
		return TakeFromPool(Location, Rotation);
	}
	UE_LOG(LogTemp, Error, TEXT("No available characters in pool! Pool size %d"), PoolSize);
	return nullptr;
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
	ExtendPool(DefaultPoolSize);
}


void UPOA_CharacterPool::OnPooledCharacterDespawn(APOA_PooledCharacter* PoolActor)
{
	SpawnedCharacterIndices.Remove(PoolActor->GetPoolIndex());
}

void UPOA_CharacterPool::ExtendPool(int count)
{
	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("UPOA_CharacterPool::BeginPlay: World is null!"));
		return;
	}

	for (int i = 0; i < count; ++i)
	{
		if (PooledCharacterClass)
		{
			APOA_PooledCharacter* NewCharacter = World->SpawnActor<APOA_PooledCharacter>(PooledCharacterClass,
				FVector().Zero(), FRotator().ZeroRotator);

			if (NewCharacter)
			{
				NewCharacter->SetActive(false);
				NewCharacter->OnPooledCharacterDespawn.AddDynamic(this, &UPOA_CharacterPool::OnPooledCharacterDespawn);
				CharacterPool.Add(NewCharacter);
				NewCharacter->SetPoolIndex(CharacterPool.Num());
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
	PoolSize += count;
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
	ExtendPool(PoolSize);
}

