// Fill out your copyright notice in the Description page of Project Settings.

#include "ENTPlayerController.h"
#include "ENTCharacter.h"
#include "ENTPlayerCameraManager.h"

AENTPlayerController::AENTPlayerController()
{
	PlayerCameraManagerClass = AENTPlayerCameraManager::StaticClass();
}

void AENTPlayerController::Possess(APawn* aPawn)
{
	Super::Possess(aPawn);

	if (aPawn->IsA(AENTCharacter::StaticClass()))
	{
		PlayerCharacter = Cast<AENTCharacter>(aPawn);
	}
}

void AENTPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AENTPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Twin stick shooter
	InputComponent->BindAxis("MoveUp", this, &ThisClass::MoveUp);
	InputComponent->BindAxis("MoveRight", this, &ThisClass::MoveRight);
	InputComponent->BindAxis("AimUp", this, &ThisClass::AimUp);
	InputComponent->BindAxis("AimRight", this, &ThisClass::AimRight);
}

void AENTPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AENTPlayerController::MoveUp(float AxisValue)
{
	if (PlayerCharacter)
	{
		
	}
}

void AENTPlayerController::MoveRight(float AxisValue)
{
	if (PlayerCharacter)
	{
		
	}
}

void AENTPlayerController::AimUp(float AxisValue)
{
	if (PlayerCharacter)
	{

	}
}

void AENTPlayerController::AimRight(float AxisValue)
{
	if (PlayerCharacter)
	{

	}
}
