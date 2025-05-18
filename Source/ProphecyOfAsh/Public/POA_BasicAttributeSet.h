

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "POA_BasicAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName)\
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName,PropertyName)\
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)\
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName)\
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class PROPHECYOFASH_API UPOA_BasicAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UPOA_BasicAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UPOA_BasicAttributeSet, Vigor)

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Control;
	ATTRIBUTE_ACCESSORS(UPOA_BasicAttributeSet, Control)

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Power;
	ATTRIBUTE_ACCESSORS(UPOA_BasicAttributeSet, Power)

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData XP;
	ATTRIBUTE_ACCESSORS(UPOA_BasicAttributeSet, XP)


};
