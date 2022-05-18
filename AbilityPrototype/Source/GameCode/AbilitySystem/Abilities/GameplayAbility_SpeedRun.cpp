// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbility_SpeedRun.h"
#include "Characters\GCBaseCharacter.h"
#include "Components\MovementComponents\GCBaseCharacterMovementComponent.h"

bool UGameplayAbility_SpeedRun::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags /*= nullptr*/, const FGameplayTagContainer* TargetTags /*= nullptr*/, OUT FGameplayTagContainer* OptionalRelevantTags /*= nullptr*/) const
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

void UGameplayAbility_SpeedRun::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData);

	AGCBaseCharacter* CachedCharacter = StaticCast<AGCBaseCharacter*>(OwnerInfo->AvatarActor.Get());
	CachedCharacter->AbilityCount--;

	MovementComponent = CachedCharacter->GetBaseCharacterMovementComponent();
	if (MovementComponent->bCanChangeBoostSpeed)
	{
		CachedSpeed = MovementComponent->GetMaxSpeed();
		MovementComponent->bCanChangeBoostSpeed = false;
	}

	MovementComponent->MaxWalkSpeed = BoostSpeed;

	UE_LOG(LogTemp, Warning, TEXT("The integer value is: %d"), CachedCharacter->AbilityCount);
}

void UGameplayAbility_SpeedRun::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);

	if (IsValid(MovementComponent))
	{
		MovementComponent->MaxWalkSpeed = (CachedSpeed != 0.0f) ? CachedSpeed : MovementComponent->GetMaxSpeed();
		MovementComponent->bCanChangeBoostSpeed = true;
	}
}
