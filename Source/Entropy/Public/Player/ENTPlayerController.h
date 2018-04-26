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

	virtual void Tick(float DeltaTime) override;

	virtual void Possess(APawn* aPawn) override;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE FString GetGamerTag() { return GamerTag; }

	void EnableController();
	void DisableController();

protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

	void MoveUp(float AxisValue);
	void MoveRight(float AxisValue);

	void ShootUp(float AxisValue);
	void ShootRight(float AxisValue);

	bool CheckRightAnalogStick();
	void UseSpecial();

protected:
	UPROPERTY()
	class AENTCharacter* PlayerCharacter;

	FString GamerTag = "";
};
