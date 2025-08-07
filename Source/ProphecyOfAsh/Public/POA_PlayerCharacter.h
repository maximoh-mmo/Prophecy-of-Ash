// Copyright 2025 Max Heinze. All Rights Reserved.
//
// This file is part of the Prophecy of Ash project.

#pragma once

#include "CoreMinimal.h"
#include "POA_Character.h"
#include "POA_PlayerCharacter.generated.h"

class UPOA_CharacterPool;

DECLARE_LOG_CATEGORY_EXTERN(LogEnemyPool, Log, All);
UCLASS(Config = Game)
class PROPHECYOFASH_API APOA_PlayerCharacter : public APOA_Character
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

protected:
	TArray<UPOA_CharacterPool> EnemyPools;

};