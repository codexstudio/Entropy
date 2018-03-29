// Fill out your copyright notice in the Description page of Project Settings.

#include "ENTCharacter.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "PaperSpriteComponent.h"
#include "Engine.h"

// Sets default values
AENTCharacter::AENTCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("Floating Pawn Movement");
	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>("Sprite Component");

	//Assign current stats
	CurrHealth = StartHealth;
	CurrMovementSpeed = StartMovementSpeed;
	CurrBasicDamage = StartBasicDamage;
	CurrBasicROF = StartBasicROF;
	CurrKnockBack = StartKnockBack;
}

// Called when the game starts or when spawned
void AENTCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AENTCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AENTCharacter::ApplyPickup(ENTCharacterClass PickupClass)
{
	AddToCurrHealth(PickupClass == GetCharacterClass() ? (int)SpecializedStatIncrement : BaseHealthIncrement);
	AddToCurrMovementSpeed(PickupClass == GetCharacterClass() ? SpecializedStatIncrement : BaseMovSpeedIncrement);
	AddToCurrBasicDamage(PickupClass == GetCharacterClass() ? SpecializedStatIncrement : BaseDamageIncrement);
	AddToCurrBasicROF(PickupClass == GetCharacterClass() ? SpecializedStatIncrement : BaseROFIncrement);
	AddToCurrKnockBack(PickupClass == GetCharacterClass() ? SpecializedStatIncrement : BaseKnockBackIncrement);
}

void AENTCharacter::UseSpecial()
{
	if (!bIsUsingSpecial && bIsSpecialReady)
	{
		bIsUsingSpecial = true;
		bIsSpecialReady = false;

		StartAttack();

		GetWorld()->GetTimerManager().SetTimer(SpecialIntervalHandle, this, &AENTCharacter::StopSpecial, SpecialInterval, false);
	}
}

void AENTCharacter::ResetSpecialCooldown()
{
	GetWorldTimerManager().ClearTimer(SpecialCooldownHandle);
	bIsSpecialReady = true;
}

void AENTCharacter::StopSpecial()
{
	GetWorldTimerManager().ClearTimer(SpecialIntervalHandle);

	bIsUsingSpecial = false;
	GetWorld()->GetTimerManager().SetTimer(SpecialCooldownHandle, this, &AENTCharacter::ResetSpecialCooldown, SpecialCooldown, false);
}

void AENTCharacter::AddToCurrHealth(int value)
{
	CurrHealth += value;
}

void AENTCharacter::AddToCurrMovementSpeed(float value)
{
	CurrMovementSpeed = (CurrMovementSpeed + value > MaxMovementSpeed) ? MaxMovementSpeed : CurrMovementSpeed += value;
}

void AENTCharacter::AddToCurrBasicDamage(float value)
{
	CurrBasicDamage += value;
}

void AENTCharacter::AddToCurrBasicROF(float value)
{
	CurrBasicROF = (CurrBasicROF + value > MaxBasicROF) ? MaxBasicROF : CurrBasicROF += value;
}

void AENTCharacter::AddToCurrKnockBack(float value)
{
	CurrKnockBack = (CurrKnockBack + value > MaxKnockBack) ? MaxKnockBack : CurrKnockBack += value;
}
