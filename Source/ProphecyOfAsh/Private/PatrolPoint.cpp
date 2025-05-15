//
// Copyright 2025 Max Heinze. All Rights Reserved.
//
// This file is part of the Prophecy of Ash project.

#include "PatrolPoint.h"

// Sets default values
APatrolPoint::APatrolPoint()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PatrolPoint"));
	MeshComponent->SetWorldLocationAndRotation(GetActorLocation(), GetActorRotation());
	MeshComponent->SetRelativeLocation(FVector(0,0,50));
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	MeshComponent->SetMobility(EComponentMobility::Static);
	MeshComponent->SetHiddenInGame(true);
	RootComponent = MeshComponent;
}

void APatrolPoint::AddNextPoint(APatrolPoint* NextPoint)
{
	if (NextPoint)
	{
		NextPatrolPoints.Add(NextPoint);
	}
}
void APatrolPoint::AddPreviousPoint(APatrolPoint* PreviousPoint)
{
	if (PreviousPoint)
	{
		PreviousPatrolPoints.Add(PreviousPoint);
	}
}
void APatrolPoint::RemovePoint()
{
	UE_LOG(LogTemp, Warning, TEXT("Removing Point %s"), *GetName());
	if (!NextPatrolPoints.IsEmpty() && !PreviousPatrolPoints.IsEmpty())
	{
		for (int i = 0; i < NextPatrolPoints.Num(); i++)
		{
			if (IsValid(NextPatrolPoints[i]))
			{
				for (int j = 0; j < PreviousPatrolPoints.Num(); j++)
				{
					if (IsValid(PreviousPatrolPoints[j]))
					{
						NextPatrolPoints[i]->AddPreviousPoint(PreviousPatrolPoints[j]);
					}
				}
			}
		}
		for (int i = 0; i < PreviousPatrolPoints.Num(); i++)
		{
			if (IsValid(PreviousPatrolPoints[i]))
			{
				for (int j = 0; j < NextPatrolPoints.Num(); j++)
				{
					if (IsValid(NextPatrolPoints[j]))
					{
						PreviousPatrolPoints[i]->AddNextPoint(NextPatrolPoints[j]);
					}
				}
			}
		}
	}
	if (!NextPatrolPoints.IsEmpty())
	{
		for (int i = 0; i < NextPatrolPoints.Num(); i++)
		{
			if (IsValid(NextPatrolPoints[i]))
			{
				NextPatrolPoints[i]->RemovePreviousPoint(this);
			}
		}
	}
	if (!PreviousPatrolPoints.IsEmpty())
	{
		for (int i = 0; i < PreviousPatrolPoints.Num(); i++)
		{
			if (IsValid(PreviousPatrolPoints[i]))
			{
				PreviousPatrolPoints[i]->RemoveNextPoint(this);
			}
		}
	}
	this->Destroy(false, true);
}

void APatrolPoint::RemovePreviousPoint(APatrolPoint* PointToRemove)
{
	UE_LOG(LogTemp, Warning, TEXT("Removing Point %s : From %s"), *PointToRemove->GetName(), *GetName());
	if (PreviousPatrolPoints.Contains(PointToRemove))
	{
		PreviousPatrolPoints.Remove(PointToRemove);
	}
}

void APatrolPoint::RemoveNextPoint(APatrolPoint* PointToRemove)
{
	UE_LOG(LogTemp, Warning, TEXT("Removing Point %s : From %s"), *PointToRemove->GetName(), *GetName());
	if (NextPatrolPoints.Contains(PointToRemove))
	{
		NextPatrolPoints.Remove(PointToRemove);
	}
}
