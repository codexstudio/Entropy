// Fill out your copyright notice in the Description page of Project Settings.

#include "ENTPlayerController.h"
#include "ENTCharacter.h"
#include "ENTPlayerCameraManager.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Online.h"
#include "Kismet/KismetSystemLibrary.h"

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

	// hopefully this will print the gamertag.. 
	if (IOnlineSubsystem::DoesInstanceExist(LIVE_SUBSYSTEM))
	{
		IOnlineIdentityPtr Ioi = IOnlineSubsystem::Get(LIVE_SUBSYSTEM)->GetIdentityInterface();
		if (Ioi.IsValid())
		{
			UKismetSystemLibrary::PrintString(this, Ioi->GetPlayerNickname(GetLocalPlayer()->GetControllerId()));
		}
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
		PlayerCharacter->AddMovementInput(FVector::RightVector, AxisValue);
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
	if (PlayerCharacter)
	{

	}
}

void AENTPlayerController::UseSpecial()
{
	if (PlayerCharacter)
	{
		PlayerCharacter->UseSpecial();
	}
}
