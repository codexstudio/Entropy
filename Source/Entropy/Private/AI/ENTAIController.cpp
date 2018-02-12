// Fill out your copyright notice in the Description page of Project Settings.

#include "ENTAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BehaviorTree.h"
#if !UE_BUILD_SHIPPING
#include "Kismet/KismetSystemLibrary.h"
#endif
#include "EntropyGameModeBase.h"
#include "Camera/ENTSharedCamera.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EngineUtils.h"

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

#if !UE_BUILD_SHIPPING
	if (!ensureAlwaysMsgf(BehaviorTreeClass != nullptr, TEXT("Did you forget to set the behavior tree class?")))
	{
		UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), "quit");
	}
#endif

	RunBehaviorTree(BehaviorTreeClass);

	AEntropyGameModeBase* const GM = (GetWorld() != nullptr) ? GetWorld()->GetAuthGameMode<AEntropyGameModeBase>() : nullptr;

	if (GM)
	{
		if (GM->GetSharedCamera() != nullptr)
		{
			GetBlackboardComponent()->SetValueAsObject("SharedCameraActor", GM->GetSharedCamera());
		}
		else
		{
			for (TActorIterator<AENTSharedCamera> Itr(GetWorld()); Itr; ++Itr)
			{
				GetBlackboardComponent()->SetValueAsObject("SharedCameraActor", *Itr);
				break;
			}
		}
	}
}
