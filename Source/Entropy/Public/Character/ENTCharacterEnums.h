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