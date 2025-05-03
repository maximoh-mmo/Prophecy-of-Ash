//
// Copyright 2025 Max Heinze. All Rights Reserved.
//
// This file is part of the Prophecy of Ash project.

#include "PatrolPoint.h"


// Sets default values
APatrolPoint::APatrolPoint()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PatrolPoint"));
	RootComponent = MeshComponent;
}
