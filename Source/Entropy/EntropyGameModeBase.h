// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "CoreMinimal.h"
#include "ENTCharacterEnums.h"
#include "GameFramework/GameModeBase.h"
#include "EntropyGameModeBase.generated.h"

class AENTSharedCamera;

UCLASS()
class ENTROPY_API AEntropyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AEntropyGameModeBase();

	UFUNCTION(BlueprintPure, Category = Camera)
	AENTSharedCamera* GetSharedCamera();

	// called from level blueprint to set shared camera to persistent camera actor 
	// that is already placed in the world
	UFUNCTION(BlueprintCallable, Category = Camera)
	void SetSharedCamera(AENTSharedCamera* InSharedCamera);

	FORCEINLINE int GetEnemiesKilled() { return EnemiesKilled; }

	void EnemyDied(bool DiedToPlayer = true);

	bool CheckLossCondition();

	UFUNCTION(BlueprintPure)
	ENTColor GetColorForPlayer(int PlayerID) const;

	UFUNCTION(BlueprintPure)
	ENTCharacterClass GetCharacterClassForPlayer(int PlayerID) const;

	UFUNCTION(BlueprintPure)
	class UPaperSprite* GetSpriteForPlayer(int PlayerID) const;
protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

	void SpawnClusterOfEnemies();

	void AttemptToScaleDifficulty();

	void GameOver();

protected:
	// you would want this in game state or game instance if this was a networked game
	AENTSharedCamera* SharedCamera;

	int EnemiesInPlay = 0;
	int EnemiesKilled = 0;

	float EnemyGlobalHealthBoost = 0;
	float EnemyGlobalSpeedBoost = 0;
	int EnemyGlobalDamageBoost = 0;

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

	UPROPERTY(EditAnywhere)
	UDataTable* ScalingDataTable;

	UPROPERTY(EditAnywhere)
	UDataTable* CharacterDataTable;

	float MinSpawnOffset;
	float MaxSpawnOffset;

	const float ClusterOffsetRange = 700.0f;

};