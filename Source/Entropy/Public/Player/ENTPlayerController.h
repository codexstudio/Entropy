// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ENTPlayerController.generated.h"

/**
 * 
 */

UCLASS()
class ENTROPY_API AENTPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AENTPlayerController();

	virtual void Possess(APawn* aPawn) override;
	
protected:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

	void MoveUp(float AxisValue);
	void MoveRight(float AxisValue);
	void AimUp(float AxisValue);
	void AimRight(float AxisValue);
	
protected:
	class AENTCharacter* PlayerCharacter;

};
