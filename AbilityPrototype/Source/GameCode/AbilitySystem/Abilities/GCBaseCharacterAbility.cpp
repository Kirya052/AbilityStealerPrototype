// Fill out your copyright notice in the Description page of Project Settings.


#include "GCBaseCharacterAbility.h"
#include "Characters\GCBaseCharacter.h"

bool UGCBaseCharacterAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags /*= nullptr*/, const FGameplayTagContainer* TargetTags /*= nullptr*/, OUT FGameplayTagContainer* OptionalRelevantTags /*= nullptr*/) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}
	if (!ActorInfo->AvatarActor->IsA<AGCBaseCharacter>())
	{
		return false;
	}

	AGCBaseCharacter* CachedCharacter = StaticCast<AGCBaseCharacter*>(ActorInfo->AvatarActor.Get());
	return CachedCharacter->CanActivateSpecialAbility();
}

void UGCBaseCharacterAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData);

	AGCBaseCharacter* CachedCharacter = StaticCast<AGCBaseCharacter*>(OwnerInfo->AvatarActor.Get());
	CachedCharacter->AbilityCount--;

	UE_LOG(LogTemp, Warning, TEXT("The integer value is: %d"), CachedCharacter->AbilityCount);
}

void UGCBaseCharacterAbility::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}
