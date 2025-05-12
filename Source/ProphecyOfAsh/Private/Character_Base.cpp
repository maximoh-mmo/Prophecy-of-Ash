//
// Copyright 2025 Max Heinze. All Rights Reserved.
//
// This file is part of the Prophecy of Ash project.

#include "Character_Base.h"


// Sets default values
A_Character_Base::A_Character_Base()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void A_Character_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void A_Character_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void A_Character_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


