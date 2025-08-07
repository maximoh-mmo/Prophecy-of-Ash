//
// Copyright 2025 Max Heinze. All Rights Reserved.
//
// This file is part of the Prophecy of Ash project.


#pragma once

#include "CoreMinimal.h"
#include "POA_Stats.generated.h"

USTRUCT(BlueprintType)
struct FPOA_Stats
{
	GENERATED_BODY()

	FPOA_Stats();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float MaxHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float CurrentHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int Vigor;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int Power;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int Control;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int XP;
};
