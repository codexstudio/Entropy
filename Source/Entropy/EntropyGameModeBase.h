// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EntropyGameModeBase.generated.h"

class AENTSharedCamera;

UCLASS()
class ENTROPY_API AEntropyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = Camera)
	AENTSharedCamera* GetSharedCamera();

	// called from level blueprint to set shared camera to persistent camera actor 
	// that is already placed in the world
	UFUNCTION(BlueprintCallable, Category = Camera)
	void SetSharedCamera(AENTSharedCamera* InSharedCamera);

	void EnemyDied(bool DiedToPlayer = true);

	bool CheckLossCondition();

protected:
	virtual void BeginPlay() override;

	void SpawnClusterOfEnemies();

	void GameOver();

protected:
	// you would want this in game state or game instance if this was a networked game
	AENTSharedCamera* SharedCamera;

	int EnemiesInPlay = 0;
	int EnemiesKilled = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Spawning)
	int MaxEnemiesInPlay;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Spawning)
	int MinEnemyClusterAmount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Spawning)
	int MaxEnemyClusterAmount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Developer Options")
	bool bAllowGameOver = true;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AENTEnemy> EnemyClass;

	float MinSpawnOffset;
	float MaxSpawnOffset;

	const float ClusterOffsetRange = 700.0f;

};