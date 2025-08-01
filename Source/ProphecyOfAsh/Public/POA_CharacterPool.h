// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "POA_PooledCharacter.h"
#include "Components/ActorComponent.h"
#include "POA_CharacterPool.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROPHECYOFASH_API UPOA_CharacterPool : public UActorComponent
{
	GENERATED_BODY()

public:
	UPOA_CharacterPool();
	// Sets default values for this component's properties

	UFUNCTION(BlueprintCallable, Category = "Character Pool")
	APOA_PooledCharacter* TakeFromPool(FVector Location, FRotator Rotation);

	UFUNCTION(BlueprintCallable, Category = "Character Pool")
	void SetPoolClass(TSubclassOf<APOA_PooledCharacter> NewPooledCharacterClass);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Pool")
	TSubclassOf<APOA_PooledCharacter> PooledCharacterClass;

	UPROPERTY(EditAnywhere, Category = "Character Pool")
	int PoolSize = 0;

	UFUNCTION()
	void OnPooledCharacterDespawn(APOA_PooledCharacter* PoolActor);

protected:
	void ExtendPool();

	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<APOA_PooledCharacter*> CharacterPool;
	TArray<int> SpawnedCharacterIndices;
	int DefaultPoolSize = 20;
	bool Extending = false;
};
