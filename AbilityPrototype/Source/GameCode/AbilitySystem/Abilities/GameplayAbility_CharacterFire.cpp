// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbility_CharacterFire.h"
#include "Characters\GCBaseCharacter.h"
#include "Components\CharacterComponents\CharacterEquipmentComponent.h"
#include "..\..\Actors\Equipment\Weapons\RangeWeaponItem.h"

bool UGameplayAbility_CharacterFire::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags /*= nullptr*/, const FGameplayTagContainer* TargetTags /*= nullptr*/, OUT FGameplayTagContainer* OptionalRelevantTags /*= nullptr*/) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}
	if (!ActorInfo->AvatarActor->IsA<AGCBaseCharacter>())
	{
		return false;
	}
	AGCBaseCharacter* Character = StaticCast<AGCBaseCharacter*>(ActorInfo->AvatarActor.Get());
	return Character->CanFire();

}

void UGameplayAbility_CharacterFire::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData);

	AGCBaseCharacter* Character = StaticCast<AGCBaseCharacter*>(OwnerInfo->AvatarActor.Get());
	Character->StartShoot();
}

void UGameplayAbility_CharacterFire::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);

	AGCBaseCharacter* Character = StaticCast<AGCBaseCharacter*>(ActorInfo->AvatarActor.Get());
	Character->StopShoot();
}
