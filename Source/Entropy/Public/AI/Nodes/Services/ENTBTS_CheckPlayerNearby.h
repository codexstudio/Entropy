// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "ENTBTS_CheckPlayerNearby.generated.h"

/**
 * 
 */
UCLASS()
class ENTROPY_API UENTBTS_CheckPlayerNearby : public UBTService
{
	GENERATED_BODY()
	
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;

	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override {}
	virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override {}
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
protected:
	UPROPERTY(EditAnywhere, Category=Blackboard)
	struct FBlackboardKeySelector SharedCameraBlackboardKey;

	UPROPERTY(EditAnywhere)
	float MaxCheckDistance;

protected:
	FName GetSharedCameraBlackboardKey() const;
};

FORCEINLINE FName UENTBTS_CheckPlayerNearby::GetSharedCameraBlackboardKey() const
{
	return SharedCameraBlackboardKey.SelectedKeyName;
}