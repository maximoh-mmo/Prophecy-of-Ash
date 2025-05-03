
//
// Copyright 2025 Max Heinze. All Rights Reserved.
//
// This file is part of the Prophecy of Ash project.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "POA_Character_Base.generated.h"

UCLASS()
class PROPHECYOFASH_API APOA_Character_Base : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APOA_Character_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
