// Fill out your copyright notice in the Description page of Project Settings.

#include "ENTBTS_CheckPlayerNearby.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/ENTAIController.h"
#include "Camera/ENTSharedCamera.h"
#include "ENTCharacter.h"

void UENTBTS_CheckPlayerNearby::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	if (AENTAIController* AIController = Cast<AENTAIController>(OwnerComp.GetAIOwner()))
	{
		if (AActor* AIActor = AIController->GetPawn())
		{
			if (UObject* KeyValue = BlackboardComp->GetValueAsObject(GetSharedCameraBlackboardKey()))
			{
				AENTSharedCamera* const SharedCamera = Cast<AENTSharedCamera>(KeyValue);
				AActor* ClosestPlayer = nullptr;
				float ClosestDistance = 0.0f;

				for (auto& Player : SharedCamera->GetPlayers())
				{
					AENTCharacter* CharRef = Cast<AENTCharacter>(Player);
					if (CharRef)
					{
						if (!CharRef->IsDead())
						{
							const float CurrDistance = FVector::Dist2D(AIActor->GetActorLocation(), Player->GetActorLocation());

							if (CurrDistance < MaxCheckDistance)
							{
								if (!ClosestPlayer || (ClosestPlayer && CurrDistance < ClosestDistance))
								{
									ClosestPlayer = Player;
									ClosestDistance = CurrDistance;
								}
							}
						}
					}
				}

				if (ClosestPlayer != nullptr)
				{
					BlackboardComp->SetValueAsObject("ClosestPlayer", ClosestPlayer);
				}
			}
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}

void UENTBTS_CheckPlayerNearby::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);
	UBlackboardData* BBAsset = GetBlackboardAsset();
	if (ensure(BBAsset))
	{
		SharedCameraBlackboardKey.ResolveSelectedKey(*BBAsset);
	}
}
