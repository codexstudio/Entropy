// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ENTCharacterEnums.h"
#include "ENTPlayerSelectWidget.generated.h"

/**
 * 
 */
UCLASS()
class ENTROPY_API UENTPlayerSelectWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintPure)
	FSlateBrush GetPlayerOneImage() const;

	UFUNCTION(BlueprintPure)
	FSlateBrush GetPlayerTwoImage() const;

	UFUNCTION(BlueprintPure)
	FSlateBrush GetPlayerThreeImage() const;

	UFUNCTION(BlueprintPure)
	FSlateBrush GetPlayerFourImage() const;

	UPROPERTY(EditAnywhere)
	UDataTable* DataTable;

protected:
	UFUNCTION(BlueprintPure)
	ENTCharacterClass GetCharacterClassForPlayer(int PlayerID) const;

	class UPaperSprite* GetSpriteForPlayer(int PlayerID) const;
	FSlateBrush MakeBrushFromSprite(UPaperSprite* Sprite, int32 Width, int32 Height) const;
};
