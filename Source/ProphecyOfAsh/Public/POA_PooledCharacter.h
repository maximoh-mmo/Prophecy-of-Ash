// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "POA_PooledCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPooledCharacterDespawn, APOA_PooledCharacter*, PoolActor);

USTRUCT()
struct FCachedCollisionState
{
	GENERATED_BODY()

	TWeakObjectPtr<UPrimitiveComponent> Component;
	ECollisionEnabled::Type CollisionEnabled;
	TEnumAsByte<ECollisionChannel> ObjectType;
	FCollisionResponseContainer CollisionResponses;
};


UCLASS()
class PROPHECYOFASH_API APOA_PooledCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APOA_PooledCharacter(const FObjectInitializer& ObjectInitializer);

	FOnPooledCharacterDespawn OnPooledCharacterDespawn;

	UFUNCTION(BlueprintCallable, Category = "Pooled Character")
	void Deactivate();

	void SetActive(bool bActivate);
	void SetPoolIndex(int32 Index);

	bool IsActive() const;
	int GetPoolIndex() const;

protected:

	bool Active;
	int32 PoolIndex;

	UPROPERTY()
	TArray<FCachedCollisionState> CachedCollisionStates;

	void DisableAllCollision();
	void CacheCollisionStates();
	void RestoreCollisionStates();
};
