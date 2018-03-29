// Fill out your copyright notice in the Description page of Project Settings.

#include "ENTPlayerController.h"
#include "ENTCharacter.h"
#include "ENTPlayerCameraManager.h"
#include "GameFramework/FloatingPawnMovement.h"

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

		PlayerCharacter->SetActorRotation(FRotator(0.0f, -90.0f, 90.0f));
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
// 	InputComponent->BindAxis("AimUp", this, &ThisClass::AimUp);
// 	InputComponent->BindAxis("AimRight", this, &ThisClass::AimRight);

	InputComponent->BindAction("UseSpecial", IE_Pressed, this, &ThisClass::UseSpecial);
}

void AENTPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AENTPlayerController::MoveUp(float AxisValue)
{
	if (PlayerCharacter && AxisValue != 0)
	{
		PlayerCharacter->AddMovementInput(FVector::ForwardVector, AxisValue);
	}
}

void AENTPlayerController::MoveRight(float AxisValue)
{
	if (PlayerCharacter && AxisValue != 0)
	{
		PlayerCharacter->AddMovementInput(FVector::RightVector, AxisValue * PlayerCharacter->GetCurrentMovementSpeed());
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

void AENTPlayerController::Shoot(FVector FireDirection)
{
	
}

void AENTPlayerController::UseSpecial()
{
	if (PlayerCharacter)
	{
		PlayerCharacter->UseSpecial();
	}
}
