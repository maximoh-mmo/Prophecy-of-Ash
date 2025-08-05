//
// Copyright 2025 Max Heinze. All Rights Reserved.
//
// This file is part of the Prophecy of Ash project.

#include "POA_PooledCharacter.h"

#include "SkeletalMeshComponentBudgeted.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "Runtime/AIModule/Classes/BrainComponent.h"

// Sets default values
APOA_PooledCharacter::APOA_PooledCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<USkeletalMeshComponentBudgeted>(ACharacter::MeshComponentName)), Active(false), PoolIndex(-1)
{
	// Set the mesh to be budgeted
	if (auto mesh =Cast<USkeletalMeshComponentBudgeted>(GetMesh()))
	{
		mesh->SetAutoRegisterWithBudgetAllocator(true);
		mesh->SetAutoCalculateSignificance(true);
	}
}

void APOA_PooledCharacter::Deactivate()
{
	Active = false;
	SetActorHiddenInGame(true);
	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController)
	{
		AIController->UnPossess();
		AIController->GetBrainComponent()->StopLogic(TEXT("Deactivated"));
		AIController->Destroy();
	}
	GetCharacterMovement()->SetComponentTickEnabled(false);

	//Save collision state and disable collision

	CacheCollisionStates();
	DisableAllCollision();
}

void APOA_PooledCharacter::SetActive(bool bActivate)
{
	Active = bActivate;
	if (!bActivate)
	{
		Deactivate();
		return;
	}
	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController)
	{
		AIController->Possess(this);
		AIController->GetBrainComponent()->RestartLogic();
	}
	else
	{
		
		AController* NewController = GetWorld()->SpawnActor<AController>(AIControllerClass, GetActorLocation(), GetActorRotation());
		if (NewController != nullptr)
		{
			// if successful will result in setting this->Controller 
			// as part of possession mechanics
			NewController->Possess(this);
		}
	}
	GetCharacterMovement()->SetComponentTickEnabled(bActivate);
	SetActorHiddenInGame(!bActivate);

	RestoreCollisionStates();
}

void APOA_PooledCharacter::SetPoolIndex(const int32 Index)
{
	PoolIndex = Index;
}

bool APOA_PooledCharacter::IsActive() const
{
	return Active;
}

int APOA_PooledCharacter::GetPoolIndex() const
{
	return PoolIndex;
}

void APOA_PooledCharacter::DisableAllCollision()
{
	TInlineComponentArray<UPrimitiveComponent*> Components;
	GetComponents<UPrimitiveComponent>(Components);
		
	for (UPrimitiveComponent* Comp : Components)
	{
		if (!Comp) continue;
		
		Comp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void APOA_PooledCharacter::CacheCollisionStates()
{
	CachedCollisionStates.Empty();

	TInlineComponentArray<UPrimitiveComponent*> Components;
	GetComponents<UPrimitiveComponent>(Components);

	for ( UPrimitiveComponent* Comp : Components)
	{
		if (!Comp) continue;
		FCachedCollisionState State;
		State.Component = Comp;
		State.CollisionEnabled = Comp->GetCollisionEnabled();
		State.ObjectType = Comp->GetCollisionObjectType();
		State.CollisionResponses = Comp->GetCollisionResponseToChannels();

		CachedCollisionStates.Add(State);
	}
}

void APOA_PooledCharacter::RestoreCollisionStates()
{
	for (const FCachedCollisionState& State : CachedCollisionStates)
	{
		if (!State.Component.IsValid()) continue;
		
		State.Component->SetCollisionEnabled(State.CollisionEnabled);
		State.Component->SetCollisionObjectType(State.ObjectType);
		State.Component->SetCollisionResponseToChannels(State.CollisionResponses);
	}
	CachedCollisionStates.Empty();
}

