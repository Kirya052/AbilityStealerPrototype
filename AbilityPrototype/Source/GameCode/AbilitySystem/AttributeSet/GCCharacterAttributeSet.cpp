// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AttributeSet/GCCharacterAttributeSet.h"

void UGCCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if (Attribute.AttributeName == FString("Health"))
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, MaxHealth.GetCurrentValue());
	}

	if (Attribute.AttributeName == FString("Stamina"))
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, MaxStamina.GetCurrentValue());
	}
}

void UGCCharacterAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	if (Attribute.AttributeName == FString("Health"))
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, MaxHealth.GetBaseValue());
	}

	if (Attribute.AttributeName == FString("Stamina"))
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, MaxStamina.GetBaseValue());
	}
}

float UGCCharacterAttributeSet::GetHealthPercent()
{
	return Health.GetCurrentValue() / MaxHealth.GetCurrentValue();
}
