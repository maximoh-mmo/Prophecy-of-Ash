

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
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UPOA_BasicAttributeSet, MaxHealth);

	//Clamp health
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

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

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Level;
	ATTRIBUTE_ACCESSORS(UPOA_BasicAttributeSet, Level)

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Attack;
	ATTRIBUTE_ACCESSORS(UPOA_BasicAttributeSet, Attack);
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
    FGameplayAttributeData ElementalAttack;
    ATTRIBUTE_ACCESSORS(UPOA_BasicAttributeSet, ElementalAttack);
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Defense;
	ATTRIBUTE_ACCESSORS(UPOA_BasicAttributeSet, Defense);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData ElementalDefense;
	ATTRIBUTE_ACCESSORS(UPOA_BasicAttributeSet, ElementalDefense);
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
    FGameplayAttributeData Skillpoints;
    ATTRIBUTE_ACCESSORS(UPOA_BasicAttributeSet, Skillpoints);

};
