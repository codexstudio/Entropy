// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ENTMenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ENTROPY_API AENTMenuPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void PlayerSelectLeft();
	
	UFUNCTION(BlueprintCallable)
	void PlayerSelectRight();

	UFUNCTION(BlueprintCallable)
	void PlayerSelectUp();

	UFUNCTION(BlueprintCallable)
	void PlayerSelectDown();

	UFUNCTION(BlueprintCallable)
	void PlayerSetDefaultClass();

private:
	class UENTLocalPlayer* MyLocalPlayer;
};
