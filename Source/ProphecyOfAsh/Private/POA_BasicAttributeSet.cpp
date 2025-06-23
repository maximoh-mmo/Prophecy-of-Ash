#include "POA_BasicAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "POA_Character.h"

void UPOA_BasicAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
}