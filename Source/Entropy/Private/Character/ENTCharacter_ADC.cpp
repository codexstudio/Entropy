// Fill out your copyright notice in the Description page of Project Settings.

#include "ENTCharacter_ADC.h"
#include "ENTProjectile.h"
#include "Engine.h"


AENTCharacter_ADC::AENTCharacter_ADC()
{
	SpecialCooldown = 2.0f;
	SpecialInterval = 2.0f;
	SpecialROF = 0.15f;
	AngleAdjuster = -250.0f;
	BulletsPerSide = 5;

	bIsSpecialReady = true;
	bIsUsingSpecial = false;

	Offset = FVector(280.0f, 0.0f, 0.0f);
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
	if (!bIsUsingSpecial)
	{
		GetWorldTimerManager().ClearTimer(SpecialAttackIntervalHandle);
	}
	if (Projectile)
	{
		FVector OffsetVelocity;
		UWorld* World = GetWorld();
		if (World)
		{
			/*FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
			AENTProjectile* SpawnedProjectile;
			if (BulletsPerSide != 0)
			{
				for (int i = -BulletsPerSide; i <= BulletsPerSide; i++)
				{
					UKismetSystemLibrary::PrintString(this, "poop");
					SpawnedProjectile = World->SpawnActor<AENTProjectile>(Projectile, GetActorLocation() + Offset*GetActorRightVector(), GetActorRotation() + FRotator(0.0f, 90.0f, 90.0f), SpawnParams);
					OffsetVelocity = FVector(SpawnedProjectile->ProjectileMovementComp->InitialSpeed, 0.0f, AngleAdjuster*i);
					SpawnedProjectile->ProjectileMovementComp->SetVelocityInLocalSpace(OffsetVelocity);
					SpawnedProjectile->Destroy(0.5f);
				}
			}*/
		}
	}
}

void AENTCharacter_ADC::StartSpecialAttack()
{
	GetWorld()->GetTimerManager().SetTimer(SpecialAttackIntervalHandle, this, &AENTCharacter_ADC::SpecialAttack, SpecialROF, true);
}