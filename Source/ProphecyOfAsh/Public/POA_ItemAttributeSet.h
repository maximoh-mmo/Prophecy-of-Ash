

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "POA_ItemAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName)\
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName,PropertyName)\
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)\
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName)\
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class PROPHECYOFASH_API UPOA_ItemAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Attack;
	ATTRIBUTE_ACCESSORS(UPOA_ItemAttributeSet, Attack);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData ElementalAttack;
	ATTRIBUTE_ACCESSORS(UPOA_ItemAttributeSet, ElementalAttack);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Defense;
	ATTRIBUTE_ACCESSORS(UPOA_ItemAttributeSet, Defense);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData ElementalDefense;
	ATTRIBUTE_ACCESSORS(UPOA_ItemAttributeSet, ElementalDefense);

};
