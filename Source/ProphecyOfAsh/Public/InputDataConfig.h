//
// Copyright 2025 Max Heinze. All Rights Reserved.
//
// This file is part of the Prophecy of Ash project.
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputDataConfig.generated.h"

class UInputAction;

UCLASS()
class PROPHECYOFASH_API UInputDataConfig : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* LookGamepadAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InteractAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* PauseAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* BasicAttackAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* SpecialAttackAction0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* SpecialAttackAction1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* SpecialAttackAction2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* ToggleLockOnAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* NextLockOnAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* PreviousLockOnAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* DodgeAction;
};