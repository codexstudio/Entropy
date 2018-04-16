// Fill out your copyright notice in the Description page of Project Settings.

#include "ENTPlayerController.h"
#include "ENTCharacter.h"
#include "ENTPlayerCameraManager.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Online.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/PlayerController.h"
#include "UnrealMathUtility.h"

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
			UKismetSystemLibrary::PrintString(this, Ioi->GetPlayerNickname(0));
		}
	}
}

void AENTPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AENTPlayerController::EnableController()
{
	EnableInput(Cast<APlayerController>(this));
}


void AENTPlayerController::DisableController()
{
	DisableInput(Cast<APlayerController>(this));
}

void AENTPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Twin stick shooter
	InputComponent->BindAxis("MoveUp", this, &ThisClass::MoveUp);
	InputComponent->BindAxis("MoveRight", this, &ThisClass::MoveRight);
 	InputComponent->BindAxis("ShootUp", this, &ThisClass::ShootUp);
	InputComponent->BindAxis("ShootRight", this, &ThisClass::ShootRight);
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

void AENTPlayerController::ShootUp(float AxisValue)
{
	if (PlayerCharacter)
	{
		if (CheckRightAnalogStick()) { return; }

		const float X = InputComponent->GetAxisValue("ShootRight");
		if (X != 0 || AxisValue != 0)
		{
			const FVector2D NormalizedVector = FVector2D(X, AxisValue).GetSafeNormal();
			const float Yaw = FMath::RadiansToDegrees(FMath::Atan2(NormalizedVector.X, NormalizedVector.Y));
			PlayerCharacter->SetActorRotation(FRotator(0, Yaw, 90.0f));

			PlayerCharacter->StartBaseAttack();
		}
		else
		{
			PlayerCharacter->StopBaseAttack();
		}
	}
	
}


void AENTPlayerController::ShootRight(float AxisValue)
{
	if (PlayerCharacter)
	{
		if (CheckRightAnalogStick()) { return; }

		const float Y = InputComponent->GetAxisValue("ShootUp");
		if (AxisValue != 0 || Y != 0)
		{
			const FVector2D NormalizedVector = FVector2D(AxisValue, Y).GetSafeNormal();
			const float Yaw = FMath::RadiansToDegrees(FMath::Atan2(NormalizedVector.Y, NormalizedVector.X));
			PlayerCharacter->SetActorRotation(FRotator(0, Yaw, 90.0f));

			PlayerCharacter->StartBaseAttack();
		}
		else
		{
			PlayerCharacter->StopBaseAttack();
		}
	}
	
}

bool AENTPlayerController::CheckRightAnalogStick()
{
	if (PlayerCharacter)
	{
		float X;
		float Y;
		GetInputAnalogStickState(EControllerAnalogStick::CAS_RightStick, X, Y);

		if (X != 0 || Y != 0)
		{
			const FVector2D NormalizedVector = FVector2D(X, Y).GetSafeNormal();
			const float Yaw = FMath::RadiansToDegrees(FMath::Atan2(NormalizedVector.Y, NormalizedVector.X));
			PlayerCharacter->SetActorRotation(FRotator(0, Yaw, 90.0f));

			PlayerCharacter->StartBaseAttack();
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return true;
	}
}

void AENTPlayerController::UseSpecial()
{
	if (PlayerCharacter)
	{
		PlayerCharacter->UseSpecial();
	}
}
