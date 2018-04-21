// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ENTCharacterEnums.h"
#include "Engine/GameInstance.h"
#include "ENTGameInstance.generated.h"


/**
 * 
 */

UCLASS()
class ENTROPY_API UENTGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	FORCEINLINE int GetLastSessionScore() { return SessionScore; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE TArray<FLeaderBoardEntry> GetLeaderBoard() { return LeaderBoard; }

	void SetLastSessionScore(int value);

protected:

	void UpdateLeaderBoard();

	void SortLeaderBoard();

	void SeverLeaderBoard(int CutOffIndice);

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "In Game Leaderboard")
	int MaxLeaderBoardSlots = 4;

	int SessionScore = 0;

	TArray<FLeaderBoardEntry> LeaderBoard;
};
