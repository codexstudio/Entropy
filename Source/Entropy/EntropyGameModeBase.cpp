// Fill out your copyright notice in the Description page of Project Settings.

#include "EntropyGameModeBase.h"
#include "Entropy.h"
#include "ENTSharedCamera.h"
#include "UnrealMathUtility.h"
#include "ENTEnemy.h"
#include "EngineUtils.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "ENTCharacter.h"
#include "ENTGameInstance.h"

static TAutoConsoleVariable<int32> CVarAllowLossConditionOverride(TEXT("dev.AllowLossCondition"), 1, TEXT("0 Disables loss condition. 1 Enables loss condition"), ECVF_SetByConsole);

void AEntropyGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	CVarAllowLossConditionOverride.AsVariable()->Set(bAllowGameOver);
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

void AEntropyGameModeBase::EnemyDied(bool DiedToPlayer)
{
	if (DiedToPlayer) {
		EnemiesKilled++;
		AttemptToScaleDifficulty();
	}

	EnemiesInPlay--;
	if (EnemiesInPlay <= (MaxEnemiesInPlay - MaxEnemyClusterAmount)) 
	{
		SpawnClusterOfEnemies();
	}
}

bool AEntropyGameModeBase::CheckLossCondition()
{
	if (CVarAllowLossConditionOverride.GetValueOnGameThread() == 0) { return false; }

	for (AActor* Player : GetSharedCamera()->GetPlayers())
	{
		AENTCharacter* ENTChar = Cast<AENTCharacter>(Player);
		if (ENTChar)
		{
			if (!ENTChar->IsDead()) { return false; }
		}
	}
	GameOver();
	return true;
}

void AEntropyGameModeBase::GameOver()
{
	UENTGameInstance* GameIns = Cast<UENTGameInstance>(GetGameInstance());
	if (GameIns)
	{
		GameIns->SetLastSessionScore(EnemiesKilled);
	}
	UGameplayStatics::OpenLevel(this, FName("GameOverMenu"));
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

	for (int i = 0; i < ClusterAmount; i++)
	{
		FVector SpawnPositionPlusOffset = SpawnPosition;
		SpawnPositionPlusOffset.X += FMath::RandRange(-ClusterOffsetRange, ClusterOffsetRange);
		SpawnPositionPlusOffset.Y += FMath::RandRange(-ClusterOffsetRange, ClusterOffsetRange);
		const FTransform SpawnTrans = FTransform(SpawnRotation, SpawnPositionPlusOffset);

		AENTEnemy* EnemyActor = GetWorld()->SpawnActorDeferred<AENTEnemy>(EnemyClass, SpawnTrans);
		EnemyActor->SpawnSetup(EnemyGlobalHealthBoost, EnemyGlobalDamageBoost);
		EnemyActor->FinishSpawning(SpawnTrans);
	}

	EnemiesInPlay += ClusterAmount;
}

void AEntropyGameModeBase::AttemptToScaleDifficulty()
{
	FString StringNumPlayers = FString::FromInt(GetSharedCamera()->GetPlayers().Num()) + "PData";
	FName DesiredRowName = FName(*StringNumPlayers);
	
	if (ScalingDataTable)
	{
		FEnemyScalingData* RowNumPlayers = ScalingDataTable->FindRow<FEnemyScalingData>(DesiredRowName, TEXT(""));

		if (RowNumPlayers && EnemiesKilled != 0 && RowNumPlayers->EnemiesKilledPerScale != 0 && EnemiesKilled % RowNumPlayers->EnemiesKilledPerScale == 0)
		{
			EnemyGlobalHealthBoost += RowNumPlayers->EnemyHealthIncrement;
			EnemyGlobalDamageBoost += RowNumPlayers->EnemyDamageOutputIncrement;
			MaxEnemiesInPlay += RowNumPlayers->MaxEnemyIncrement;
			MinEnemyClusterAmount += RowNumPlayers->MinClusterIncrement;
			MaxEnemyClusterAmount += RowNumPlayers->MaxClusterIncrement;
		}
		//UKismetSystemLibrary::PrintString(this, "RRRR :" + FString::SanitizeFloat(RowNumPlayers->EnemiesKilledPerScale));
	}
}
