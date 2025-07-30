// Fill out your copyright notice in the Description page of Project Settings.


#include "POA_PooledCharacter.h"

// Sets default values
APOA_PooledCharacter::APOA_PooledCharacter() : Active(false), PoolIndex(-1)
{
}

void APOA_PooledCharacter::Deactivate()
{
	Active = false;
	SetActorHiddenInGame(true);
}

void APOA_PooledCharacter::SetActive(bool bActivate)
{
	Active = bActivate;
	SetActorHiddenInGame(!bActivate);
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

