// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ENTCharacterEnums.generated.h"

UENUM()
enum class ENTCharacterClass : uint8
{
	Assassin,
	Tank,
	ADC,
	Bruiser,
	NONE
};

UENUM()
enum class ENTProjectileType : uint8
{
	PlayerProjectile,
	EnemyProjectile,
	NONE
};

template<typename T>
FName EnumToFName(const FString& enumName, const T value) {
	UEnum* pEnum = FindObject<UEnum>(ANY_PACKAGE, *enumName);
	FString temp = *(pEnum ? pEnum->GetNameStringByIndex(static_cast<uint8>(value)) : "null");
	return FName(*temp);
};

USTRUCT(Blueprintable)
struct FPickupSpriteData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ENTCharacterClass CharacterClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UPaperSprite* PaperSprite;
};

USTRUCT(Blueprintable)
struct FEnemyScalingData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "Every nth enemy killed will cause all values below to be added to the appropriate game stats."))
	int EnemiesKilledPerScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "How much additional health enemies get on top of their starting health."))
	float EnemyHealthIncrement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "How much additional damage enemies output on top of their starting damage."))
	int EnemyDamageOutputIncrement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "How much to increment the max enemy allowance in the level."))
	int MaxEnemyIncrement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "How much to increment the min enemy spawn cluster in the level."))
	int MinClusterIncrement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "How much to increment the max enemy spawn cluster in the level."))
	int MaxClusterIncrement;
};

USTRUCT(BlueprintType)
struct FLeaderBoardEntry
{
	GENERATED_BODY()

public:
	FLeaderBoardEntry()
	{
		Team = FString("");
		Score = 0;
	}

	FLeaderBoardEntry(FString TeamValue, int ScoreValue) 
	{
		Team = TeamValue;
		Score = ScoreValue;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Team;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Score;
};