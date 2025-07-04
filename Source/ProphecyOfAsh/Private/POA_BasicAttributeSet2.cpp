#include "POA_BasicAttributeSet2.h"
#include "AbilitySystemComponent.h"

void UPOA_BasicAttributeSet2::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetCombinedHealthMax());
	}

	if (Attribute == GetBaseHealthAttribute() || Attribute == GetVigorDerivedHealthAttribute())
	{
		bIsAtMaxHealth = FMath::Abs(GetHealth() - GetCombinedHealthMax()) <= 0.1f;
	}

	if (Attribute == GetXPAttribute())
	{
		GetOwningAbilitySystemComponent()->SetNumericAttributeBase(GetCumulativeXPAttribute(), GetCumulativeXP()+NewValue);

		if (NewValue >= XPToNextLevel(GetLevel()))
		{
			NewValue -= XPToNextLevel(GetLevel());
			GetOwningAbilitySystemComponent()->SetNumericAttributeBase(GetXPAttribute(), NewValue);
			GetOwningAbilitySystemComponent()->SetNumericAttributeBase(GetLevelAttribute(), Level.GetBaseValue() + 1);
		}
	}
}

void UPOA_BasicAttributeSet2::PostAttributeBaseChange(const FGameplayAttribute& Attribute, float OldValue,
	float NewValue) const
{
	Super::PostAttributeBaseChange(Attribute, OldValue, NewValue);

	if (Attribute == GetLevelAttribute())
	{
		// Level up logic
		GetOwningAbilitySystemComponent()->SetNumericAttributeBase(GetBaseHealthAttribute(), GetBaseHealth() - HPAtLevel(OldValue) + HPAtLevel(NewValue));
		GetOwningAbilitySystemComponent()->SetNumericAttributeBase(GetPowerAttribute(), GetPower() - PowerAtLevel(OldValue) + PowerAtLevel(NewValue));
		GetOwningAbilitySystemComponent()->SetNumericAttributeBase(GetVigorAttribute(), GetVigor() - VigorAtLevel(OldValue) + VigorAtLevel(NewValue));
		GetOwningAbilitySystemComponent()->SetNumericAttributeBase(GetControlAttribute(), GetControl() - ControlAtLevel(OldValue) + ControlAtLevel(NewValue));
	}
	// If the base health attribute is changed, update the combined health max attribute
	if (Attribute == GetBaseHealthAttribute() || Attribute == GetVigorDerivedHealthAttribute())
	{
		// Ensure the combined health max is updated correctly
		GetOwningAbilitySystemComponent()->SetNumericAttributeBase(GetCombinedHealthMaxAttribute(),GetBaseHealth()+GetVigorDerivedHealth());
		if (bIsAtMaxHealth)
		{
			GetOwningAbilitySystemComponent()->SetNumericAttributeBase(GetHealthAttribute(), GetCombinedHealthMax());
		}
	}
	if (Attribute == GetBasePowerAttribute())
	{
		GetOwningAbilitySystemComponent()->SetNumericAttributeBase(GetPhysicalDamageAttribute(), NewValue * 10);
	}
	if (Attribute == GetBaseControlAttribute())
	{
		GetOwningAbilitySystemComponent()->SetNumericAttributeBase(GetElementalDamageAttribute(), NewValue * 5);
		GetOwningAbilitySystemComponent()->SetNumericAttributeBase(GetElementalDefenseAttribute(), 1+0.8*(NewValue - ControlAtLevel(1)));
	}
	if (Attribute == GetBaseVigorAttribute())
	{
		GetOwningAbilitySystemComponent()->SetNumericAttributeBase(GetVigorDerivedHealthAttribute(), GetVigorFactor()* (NewValue - 5));
		GetOwningAbilitySystemComponent()->SetNumericAttributeBase(GetCombinedHealthMaxAttribute(),GetBaseHealth()+GetVigorDerivedHealth());
		if (bIsAtMaxHealth)
		{
			GetOwningAbilitySystemComponent()->SetNumericAttributeBase(GetHealthAttribute(), GetCombinedHealthMax());
		}
	}
}

float UPOA_BasicAttributeSet2::HPAtLevel(float level)
{
	return 100.0 + (level - 1) * (10 * level -8);
}

float UPOA_BasicAttributeSet2::PowerAtLevel(float level)
{
	return 1.2 * FMath::Pow(1.25, level - 2);
}

float UPOA_BasicAttributeSet2::ControlAtLevel(float level)
{
	return 1.0 * FMath::Pow(1.16, level - 2);
}

float UPOA_BasicAttributeSet2::VigorAtLevel(float level)
{
	return 6.0 * FMath::Pow(1.13, level - 2);
}

float UPOA_BasicAttributeSet2::XPToNextLevel(float level)
{
	return 100.0 * FMath::Pow(1.35, level - 1);
}
