// Fill out your copyright notice in the Description page of Project Settings.

#include "EntropyGameModeBase.h"
#include "Entropy.h"
#include "ENTSharedCamera.h"
#include "UnrealMathUtility.h"
#include "ENTEnemy.h"
#include "EngineUtils.h"

void AEntropyGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
}

AENTSharedCamera* AEntropyGameModeBase::GetSharedCamera()
{
	if (SharedCamera)
	{
		return SharedCamera;
	}
	else
	{
		for (TActorIterator<AENTSharedCamera> Itr(GetWorld()); Itr; ++Itr)
		{
			return *Itr;
		}
	}
	return nullptr;
}

void AEntropyGameModeBase::SetSharedCamera(AENTSharedCamera* InSharedCamera)
{
	SharedCamera = InSharedCamera;

	MinSpawnOffset = SharedCamera->GetOrthoWidth() * 1.05f;
	MaxSpawnOffset = MinSpawnOffset * 1.5f;

	while (EnemiesInPlay < MaxEnemiesInPlay)
	{
		SpawnClusterOfEnemies();
	}
}

void AEntropyGameModeBase::EnemyDied()
{
	EnemiesInPlay--;
	if (EnemiesInPlay <= (MaxEnemiesInPlay - MaxEnemyClusterAmount)) 
	{
		SpawnClusterOfEnemies();
	}
}

void AEntropyGameModeBase::SpawnClusterOfEnemies()
{
	int ClusterAmount = FMath::RandRange(MinEnemyClusterAmount, MaxEnemyClusterAmount);
	float Angle = FMath::RandRange(0.0f, 2 * PI);
	float Offset = FMath::RandRange(MinSpawnOffset, MaxSpawnOffset);
	FVector SpawnPosition = FVector(Offset * FMath::Cos(Angle) + SharedCamera->GetActorLocation().X,
									Offset * FMath::Sin(Angle) + SharedCamera->GetActorLocation().Y,
									0);
	FRotator SpawnRotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;

	for (int i = 0; i < ClusterAmount; i++)
	{
		FVector SpawnPositionPlusOffset = SpawnPosition;
		SpawnPositionPlusOffset.X += FMath::RandRange(-ClusterOffsetRange, ClusterOffsetRange);
		SpawnPositionPlusOffset.Y += FMath::RandRange(-ClusterOffsetRange, ClusterOffsetRange);
		GetWorld()->SpawnActor<AENTEnemy>(EnemyClass, SpawnPositionPlusOffset, SpawnRotation, SpawnInfo);
	}

	EnemiesInPlay += ClusterAmount;
}