// Fill out your copyright notice in the Description page of Project Settings.

#include "ENTAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BehaviorTree.h"

AENTAIController::AENTAIController()
{
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("SightConfig");
	AIPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>("Perception Component");
	SetPerceptionComponent(*AIPerceptionComp);

	AIPerceptionComp->ConfigureSense(*SightConfig);
	AIPerceptionComp->SetDominantSense(UAISense_Sight::StaticClass());
}

void AENTAIController::BeginPlay()
{
	Super::BeginPlay();
	if (!ensureAlwaysMsgf(BehaviorTreeClass != nullptr, TEXT("Did you forget to set the behavior tree class?")))
	{
		GetWorld()->Exec(GetWorld(), TEXT("quit"));
	}

	RunBehaviorTree(BehaviorTreeClass);
}
