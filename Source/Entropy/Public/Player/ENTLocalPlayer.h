// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LocalPlayer.h"
#include "ENTCharacterEnums.h"
#include "ENTLocalPlayer.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ENTROPY_API UENTLocalPlayer : public ULocalPlayer
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	FColor PlayerColor;
	
	UPROPERTY(BlueprintReadWrite)
	ENTCharacterClass PlayerClass;
};
