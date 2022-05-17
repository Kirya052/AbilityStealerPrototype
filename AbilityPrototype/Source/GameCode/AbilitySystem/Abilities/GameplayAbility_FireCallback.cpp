// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbility_FireCallback.h"
#include "Characters\GCBaseCharacter.h"
#include "GameCodeTypes.h"
#include "..\AttributeSet\GCCharacterAttributeSet.h"

bool UGameplayAbility_FireCallback::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags /*= nullptr*/, const FGameplayTagContainer* TargetTags /*= nullptr*/, OUT FGameplayTagContainer* OptionalRelevantTags /*= nullptr*/) const
{
	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}

void UGameplayAbility_FireCallback::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData);

	AGCBaseCharacter* Character = StaticCast<AGCBaseCharacter*>(OwnerInfo->AvatarActor.Get());
	float Health = Character->GetCharacterAttributeSet()->Health.GetCurrentValue();
	UE_LOG(LogTemp, Warning, TEXT("FireCallBack Active, health: %f"), Health);
}

void UGameplayAbility_FireCallback::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);

	AGCBaseCharacter* Character = StaticCast<AGCBaseCharacter*>(ActorInfo->AvatarActor.Get());
	float Health = Character->GetCharacterAttributeSet()->Health.GetCurrentValue();
	UE_LOG(LogTemp, Warning, TEXT("FireCallBack deactivate, health: %f"), Health);
}
