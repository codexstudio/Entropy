// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ENTAIController.generated.h"

/**
 * 
 */
UCLASS()
class ENTROPY_API AENTAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AENTAIController();

	bool GetIsStunned();
	void SetIsStunned(bool value);
	void SetLastAttacker(AActor* Attacker);
	
protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, Category = AI)
	class UAIPerceptionComponent* AIPerceptionComp;
	class UAISenseConfig_Sight* SightConfig;
	
	UPROPERTY(EditAnywhere, Category = AI)
	class UBehaviorTree* BehaviorTreeClass;

	
};
