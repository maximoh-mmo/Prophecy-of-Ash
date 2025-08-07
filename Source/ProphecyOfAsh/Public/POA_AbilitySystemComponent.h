//
// Copyright 2025 Max Heinze. All Rights Reserved.
//
// This file is part of the Prophecy of Ash project.

#pragma once

#include "AbilitySystemComponent.h"
#include "CoreMinimal.h"  
#include "GameplayTagContainer.h"
#include "POA_AbilitySystemComponent.generated.h"  

class UPOAGameplayAbility;  

UCLASS()  
class PROPHECYOFASH_API UPOA_AbilitySystemComponent : public UAbilitySystemComponent
{  
   GENERATED_BODY()  

public:      
   // Sets default values for this component's properties  
   UPOA_AbilitySystemComponent();  

   void GetActiveAbilitesWithTags(const FGameplayTagContainer& GameplayTagContainer, TArray<TSubclassOf<UPOAGameplayAbility>>& ActiveAbilities) const;  

   int32 GetDefaultAbilityLevel() const;  

   static UPOA_AbilitySystemComponent* GetAbilitySystemComponentFromActor(const AActor* Actor, bool LookForComponent = false);  
};
