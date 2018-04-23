// Fill out your copyright notice in the Description page of Project Settings.

#include "ENTMenuPlayerController.h"
#include "ENTLocalPlayer.h"
#include "UnrealMathUtility.h"
#include "Kismet/KismetSystemLibrary.h"

void AENTMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AENTMenuPlayerController::PlayerSelectLeft()
{
	if (UENTLocalPlayer* MyLocalPlayer = Cast<UENTLocalPlayer>(GetLocalPlayer()))
	{
		MyLocalPlayer->PlayerClass = (ENTCharacterClass)(((int)MyLocalPlayer->PlayerClass - 1) % 4);
		if ((int)MyLocalPlayer->PlayerClass == 255) MyLocalPlayer->PlayerClass = (ENTCharacterClass)3;
		UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("%d"), (uint8)MyLocalPlayer->PlayerClass));
	}
}

void AENTMenuPlayerController::PlayerSelectRight()
{
	if (UENTLocalPlayer* MyLocalPlayer = Cast<UENTLocalPlayer>(GetLocalPlayer()))
	{
		MyLocalPlayer->PlayerClass = (ENTCharacterClass)(((int)MyLocalPlayer->PlayerClass + 1) % 4);
		UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("%d"), (uint8)MyLocalPlayer->PlayerClass));
	}
}

void AENTMenuPlayerController::PlayerSelectUp()
{
	if (UENTLocalPlayer* MyLocalPlayer = Cast<UENTLocalPlayer>(GetLocalPlayer()))
	{
		MyLocalPlayer->PlayerColor = (ENTColor)(((int)MyLocalPlayer->PlayerColor + 1) % 4);
		UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("%d"), (uint8)MyLocalPlayer->PlayerColor));
	}
}

void AENTMenuPlayerController::PlayerSelectDown()
{
	if (UENTLocalPlayer* MyLocalPlayer = Cast<UENTLocalPlayer>(GetLocalPlayer()))
	{
		MyLocalPlayer->PlayerColor = (ENTColor)(((int)MyLocalPlayer->PlayerColor - 1) % 4);
		if ((int)MyLocalPlayer->PlayerColor == 255) MyLocalPlayer->PlayerColor = (ENTColor)3;
		UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("%d"), (uint8)MyLocalPlayer->PlayerColor));
	}
}

void AENTMenuPlayerController::PlayerSetDefaultClass()
{
	if (UENTLocalPlayer* MyLocalPlayer = Cast<UENTLocalPlayer>(GetLocalPlayer()))
	{
		MyLocalPlayer->PlayerClass = ENTCharacterClass::ADC;
	}
}
