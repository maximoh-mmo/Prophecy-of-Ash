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
	UInputAction* MoveForwardAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* MoveRightAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* MoveCameraInAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* TurnAction;
};