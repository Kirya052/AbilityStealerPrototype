// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Controllers/GCAIController.h"
#include "GCAICharacterController.generated.h"

/**
 * 
 */
UCLASS()
class GAMECODE_API AGCAICharacterController : public AGCAIController
{
	GENERATED_BODY()

public:
	virtual void SetPawn(APawn* InPawn) override;

	virtual void ActorsPerceptionUpdated(const TArray<AActor*>& UpdatedActors) override;

	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Behaviour")
	bool bIsCanStartBehaviourTree = false;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	float TargetReachRadius = 100.0f;

	void SetupPatrolling();

private:
	void TryMoveToNextTarget();

	bool IsTargetReached(FVector TargetLocation) const;

	TWeakObjectPtr<class AGCAICharacter> CachedAICharacter;

	bool bIsPatrolling = false;
};
