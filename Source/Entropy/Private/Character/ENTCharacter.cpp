// Fill out your copyright notice in the Description page of Project Settings.

#include "ENTCharacter.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "PaperSpriteComponent.h"
#include "Engine.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AENTCharacter::AENTCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("Floating Pawn Movement");
	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>("Sprite Component");

}

// Called when the game starts or when spawned
void AENTCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetActorRotation(FRotator(0.0f, -90.0f, 90.0f));

	//Assign current stats
	CurrHealth = StartHealth;
	CurrMovementSpeed = StartMovementSpeed;
	MyPawnMovement->MaxSpeed = CurrMovementSpeed;
	CurrBasicDamage = StartBasicDamage;
	CurrBasicROF = StartBasicROF;
	CurrKnockBack = StartKnockBack;
}

// Called every frame
void AENTCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AENTCharacter::ApplyPickup(ENTCharacterClass PickupClass)
{
	AddToCurrHealth((GetCharacterClass() == ENTCharacterClass::Tank && PickupClass == GetCharacterClass()) ? (int)SpecializedStatIncrement : BaseHealthIncrement);
	AddToCurrMovementSpeed((GetCharacterClass() == ENTCharacterClass::Assassin && PickupClass == GetCharacterClass()) ? SpecializedStatIncrement : BaseMovSpeedIncrement);
	AddToCurrBasicDamage(BaseDamageIncrement);
	AddToCurrBasicROF((GetCharacterClass() == ENTCharacterClass::ADC && PickupClass == GetCharacterClass()) ? SpecializedStatIncrement : BaseROFIncrement);
	AddToCurrKnockBack((GetCharacterClass() == ENTCharacterClass::Bruiser && PickupClass == GetCharacterClass()) ? SpecializedStatIncrement : BaseKnockBackIncrement);
}


void AENTCharacter::ReceiveDamage(uint32 dmg)
{
	UKismetSystemLibrary::PrintString(this, "Damage Taken. Health :" + FString::FromInt(CurrHealth - dmg));
	if ((CurrHealth - dmg) <= 0) {
		Die();
	}
	else {
		CurrHealth -= dmg;
	}
}

void AENTCharacter::Die()
{
	//Disable sprite renderer
	//Disable colliders
	//Disable input
	//Wait for secs
	Respawn();
}

void AENTCharacter::Respawn()
{
	//ReEnable sprite renderer
	//ReEnable colliders
	//ReEnable input
	//Set transform position x & y to camera x & y
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
	UKismetSystemLibrary::PrintString(this, "Health :" + FString::SanitizeFloat(CurrHealth));
}

void AENTCharacter::AddToCurrMovementSpeed(float value)
{
	CurrMovementSpeed = (CurrMovementSpeed + value > MaxMovementSpeed) ? MaxMovementSpeed : CurrMovementSpeed += value;
	MyPawnMovement->MaxSpeed = CurrMovementSpeed;
	UKismetSystemLibrary::PrintString(this, "Movement Speed :" + FString::SanitizeFloat(CurrMovementSpeed));
}

void AENTCharacter::AddToCurrBasicDamage(float value)
{
	CurrBasicDamage += value;
	UKismetSystemLibrary::PrintString(this, "Damage :" + FString::SanitizeFloat(CurrBasicDamage));
}

void AENTCharacter::AddToCurrBasicROF(float value)
{
	CurrBasicROF = (CurrBasicROF + value > MaxBasicROF) ? MaxBasicROF : CurrBasicROF += value;
	UKismetSystemLibrary::PrintString(this, "ROF :" + FString::SanitizeFloat(CurrBasicROF));
}

void AENTCharacter::AddToCurrKnockBack(float value)
{
	CurrKnockBack = (CurrKnockBack + value > MaxKnockBack) ? MaxKnockBack : CurrKnockBack += value;
	UKismetSystemLibrary::PrintString(this, "Knock Back :" + FString::SanitizeFloat(CurrKnockBack));
}
