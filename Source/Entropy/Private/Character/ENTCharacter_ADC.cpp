// Fill out your copyright notice in the Description page of Project Settings.

#include "ENTCharacter_ADC.h"
#include "Engine.h"

AENTCharacter_ADC::AENTCharacter_ADC()
{
	SpecialCooldown = 2.0f;
	SpecialInterval = 2.0f;

	bIsSpecialReady = true;
	bIsUsingSpecial = false;
}

void AENTCharacter_ADC::BeginPlay()
{
	Super::BeginPlay();
}

void AENTCharacter_ADC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AENTCharacter_ADC::SpecialAttack()
{
	
}

void AENTCharacter_ADC::UseSpecial()
{
	Super::UseSpecial();
}

void AENTCharacter_ADC::ResetSpecialCooldown()
{
	Super::ResetSpecialCooldown();
}

void AENTCharacter_ADC::StopSpecial()
{
	Super::StopSpecial();
}
