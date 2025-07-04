//
// Copyright 2025 Max Heinze. All Rights Reserved.
//
// This file is part of the Prophecy of Ash project.

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
class PROPHECYOFASH_API UPOA_BasicAttributeSet2 : public UAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Combined Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UPOA_BasicAttributeSet2, Health);

	UPROPERTY(BlueprintReadOnly, Category = "Combined Attributes")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UPOA_BasicAttributeSet2, Vigor)

	UPROPERTY(BlueprintReadOnly, Category = "Combined Attributes")
	FGameplayAttributeData Control;
	ATTRIBUTE_ACCESSORS(UPOA_BasicAttributeSet2, Control)

	UPROPERTY(BlueprintReadOnly, Category = "Combined Attributes")
	FGameplayAttributeData Power;
	ATTRIBUTE_ACCESSORS(UPOA_BasicAttributeSet2, Power)

	UPROPERTY(BlueprintReadOnly, Category = "Base Attributes")
	FGameplayAttributeData BaseHealth;
	ATTRIBUTE_ACCESSORS(UPOA_BasicAttributeSet2, BaseHealth);

	UPROPERTY(BlueprintReadOnly, Category = "Base Attributes")
	FGameplayAttributeData BasePower;
	ATTRIBUTE_ACCESSORS(UPOA_BasicAttributeSet2, BasePower);

	UPROPERTY(BlueprintReadOnly, Category = "Base Attributes")
	FGameplayAttributeData BaseControl;
	ATTRIBUTE_ACCESSORS(UPOA_BasicAttributeSet2, BaseControl);

	UPROPERTY(BlueprintReadOnly, Category = "Base Attributes")
	FGameplayAttributeData BaseVigor;
	ATTRIBUTE_ACCESSORS(UPOA_BasicAttributeSet2, BaseVigor);

	UPROPERTY(BlueprintReadOnly, Category = "Base Attributes")
	FGameplayAttributeData XP;
	ATTRIBUTE_ACCESSORS(UPOA_BasicAttributeSet2, XP)

	UPROPERTY(BlueprintReadOnly, Category = "Derived Attributes")
	FGameplayAttributeData VigorDerivedHealth;
	ATTRIBUTE_ACCESSORS(UPOA_BasicAttributeSet2, VigorDerivedHealth);

	UPROPERTY(BlueprintReadOnly, Category = "Derived Attributes")
	FGameplayAttributeData CombinedHealthMax;
	ATTRIBUTE_ACCESSORS(UPOA_BasicAttributeSet2, CombinedHealthMax);

	UPROPERTY(BlueprintReadOnly, Category = "Derived Attributes")
	FGameplayAttributeData CumulativeXP;
	ATTRIBUTE_ACCESSORS(UPOA_BasicAttributeSet2, CumulativeXP)

	UPROPERTY(BlueprintReadOnly, Category = "Derived Attributes")
	FGameplayAttributeData CurrentLevelXP;
	ATTRIBUTE_ACCESSORS(UPOA_BasicAttributeSet2, CurrentLevelXP)

	UPROPERTY(BlueprintReadOnly, Category = "Derived Attributes")
	FGameplayAttributeData Level;
	ATTRIBUTE_ACCESSORS(UPOA_BasicAttributeSet2, Level)

	UPROPERTY(BlueprintReadOnly, Category = "Derived Attributes")
	FGameplayAttributeData PhysicalDefense;
	ATTRIBUTE_ACCESSORS(UPOA_BasicAttributeSet2, PhysicalDefense);

	UPROPERTY(BlueprintReadOnly, Category = "Derived Attributes")
	FGameplayAttributeData ElementalDefense;
	ATTRIBUTE_ACCESSORS(UPOA_BasicAttributeSet2, ElementalDefense);

	UPROPERTY(BlueprintReadOnly, Category = "Derived Attributes")
	FGameplayAttributeData PhysicalDamage;
	ATTRIBUTE_ACCESSORS(UPOA_BasicAttributeSet2, PhysicalDamage);

	UPROPERTY(BlueprintReadOnly, Category = "Derived Attributes")
	FGameplayAttributeData ElementalDamage;
	ATTRIBUTE_ACCESSORS(UPOA_BasicAttributeSet2, ElementalDamage);

	UPROPERTY(BlueprintReadOnly, Category = "Combat Attributes")
	FGameplayAttributeData BasicAttackMultiplier;
	ATTRIBUTE_ACCESSORS(UPOA_BasicAttributeSet2, BasicAttackMultiplier);

	UPROPERTY(BlueprintReadOnly, Category = "Combat Attributes")
	FGameplayAttributeData CleaveAttackMultiplier;
	ATTRIBUTE_ACCESSORS(UPOA_BasicAttributeSet2, CleaveAttackMultiplier);

	UPROPERTY(BlueprintReadOnly, Category = "Combat Attributes")
	FGameplayAttributeData RangeAttackMultiplier;
	ATTRIBUTE_ACCESSORS(UPOA_BasicAttributeSet2, RangeAttackMultiplier);

	UPROPERTY(BlueprintReadOnly, Category = "Combat Attributes")
	FGameplayAttributeData CleaveAttackCooldown;
	ATTRIBUTE_ACCESSORS(UPOA_BasicAttributeSet2, CleaveAttackCooldown);

	UPROPERTY(BlueprintReadOnly, Category = "Combat Attributes")
	FGameplayAttributeData RangeAttackCooldown;
	ATTRIBUTE_ACCESSORS(UPOA_BasicAttributeSet2, RangeAttackCooldown);

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData VigorFactor = 8.0f; // Default value for VigorFactor
	ATTRIBUTE_ACCESSORS(UPOA_BasicAttributeSet2, VigorFactor)

	//Clamp health
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	// Called after an attribute value has changed, for derived attributes
	virtual void PostAttributeBaseChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) const override;

private:
	bool bIsAtMaxHealth = false;
	static float HPAtLevel(float level);
	static float PowerAtLevel(float level);
	static float ControlAtLevel(float level);
	static float VigorAtLevel(float level);
	static float XPToNextLevel(float level);
	static float HPDerived(float Vigor);
	static float PDefDerived(float vigor);
	static 
};
