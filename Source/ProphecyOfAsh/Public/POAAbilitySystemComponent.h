#pragma once
#include "AbilitySystemComponent.h"
#include "CoreMinimal.h"  
#include "GameplayTagContainer.h"
#include "POAAbilitySystemComponent.generated.h"  

class UPOAGameplayAbility;  

UCLASS()  
class PROPHECYOFASH_API UPOAAbilitySystemComponent : public UAbilitySystemComponent
{  
   GENERATED_BODY()  

public:      
   // Sets default values for this component's properties  
   UPOAAbilitySystemComponent();  

   void GetActiveAbilitesWithTags(const FGameplayTagContainer& GameplayTagContainer, TArray<TSubclassOf<UPOAGameplayAbility>>& ActiveAbilities) const;  

   int32 GetDefaultAbilityLevel() const;  

   static UPOAAbilitySystemComponent* GetAbilitySystemComponentFromActor(const AActor* Actor, bool LookForComponent = false);  
};
