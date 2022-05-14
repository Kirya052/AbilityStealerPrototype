// Fill out your copyright notice in the Description page of Project Settings.


#include "GCAbilitySystemComponent.h"

bool UGCAbilitySystemComponent::TryActivateAbilityWithTag(FGameplayTag GameplayTag, bool bAllowRemoteActivation /*= true*/)
{
	return TryActivateAbilitiesByTag(FGameplayTagContainer(GameplayTag), bAllowRemoteActivation);
}

bool UGCAbilitySystemComponent::TryCancelAbilityWithTag(FGameplayTag GameplayTag)
{
	bool Result = false;
	TArray<FGameplayAbilitySpec*> AbilitiesToActivate;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(FGameplayTagContainer(GameplayTag), AbilitiesToActivate, false);

	// Iterate the list of all ability specs
	for (FGameplayAbilitySpec* Spec : AbilitiesToActivate)
	{
		// Iterate all instances on this ability spec
		TArray<UGameplayAbility*> AbilityInstances = Spec->GetAbilityInstances();

		for (UGameplayAbility* ActiveAbility : AbilityInstances)
		{
			ActiveAbility->K2_CancelAbility();
			Result = true;
		}
	}
	return Result;
}

bool UGCAbilitySystemComponent::IsAbilityActive(FGameplayTag GameplayTag)
{
	bool Result = false;
	TArray<FGameplayAbilitySpec*> AbilitiesToActivate;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(FGameplayTagContainer(GameplayTag), AbilitiesToActivate, false);

	// Iterate the list of all ability specs
	for (FGameplayAbilitySpec* Spec : AbilitiesToActivate)
	{
		// Iterate all instances on this ability spec
		TArray<UGameplayAbility*> AbilityInstances = Spec->GetAbilityInstances();

		for (UGameplayAbility* ActiveAbility : AbilityInstances)
		{
			Result |= ActiveAbility->IsActive();
		}
	}
	return Result;
}
