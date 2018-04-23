// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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
	class UDataTable* DataTable;
};
