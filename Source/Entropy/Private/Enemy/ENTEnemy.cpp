// Fill out your copyright notice in the Description page of Project Settings.

#include "ENTEnemy.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "PaperSpriteComponent.h"
#include "ENTCharacter.h"
#include "UnrealMathUtility.h"
#include "EntropyGameModeBase.h"
#include "ENTSharedCamera.h"
#include "ENTPickup.h"


// Sets default values
AENTEnemy::AENTEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("Box Component");
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	BoxComponent->SetBoxExtent(FVector(600.0f, 600.0f, 1000.0f));
	RootComponent = BoxComponent;

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>("Sprite Component");
	SpriteComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	SpriteComponent->SetupAttachment(RootComponent);

	FPMovComponent = CreateDefaultSubobject<UFloatingPawnMovement>("Floating Pawn Movement");
	FPMovComponent->MaxSpeed = 600.0f;
	FPMovComponent->Acceleration = 1000.0f;
	FPMovComponent->Deceleration = 2000.0f;
	FPMovComponent->TurningBoost = 8.0f;

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AENTEnemy::OnCollisionEnter);
}

// Called when the game starts or when spawned
void AENTEnemy::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->SetRelativeScale3D(FVector(0.25, 0.25, 0.25));
	SpriteComponent->SetRelativeRotation(FRotator(0, -90, 90));
	CurrHealth = StartHealth;

	GameMode = (GetWorld() != nullptr) ? GetWorld()->GetAuthGameMode<AEntropyGameModeBase>() : nullptr;
}

// Called every frame
void AENTEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CameraLoc;
	if (GameMode)
	{
		if (GameMode->GetSharedCamera() != nullptr)
		{
			CameraLoc =  GameMode->GetSharedCamera()->GetActorLocation();
		}
	}
	else
	{
		GameMode = (GetWorld() != nullptr) ? GetWorld()->GetAuthGameMode<AEntropyGameModeBase>() : nullptr;
	}
	if (FVector::Dist(this->GetActorLocation(), CameraLoc) > MaxDistanceFromCamera)
	{
		Die(false);
	}
}

// Called to bind functionality to input
void AENTEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AENTEnemy::ReceiveDamage(float Dmg)
{
	UKismetSystemLibrary::PrintString(this, "Enemy Taking Fire!!!");
	if ((CurrHealth - Dmg) <= 0) 
	{
		Die();
	}
	else {
		CurrHealth -= Dmg;
	}
}

void AENTEnemy::Die(bool DiedToPlayer)
{
	if (DiedToPlayer)
	{
		UKismetSystemLibrary::PrintString(this, "Enemy Down!!!");
		float RandNum = FMath::RandRange(0.0f, 100.0f);
		if (RandNum <= ChanceToDropPickup)
		{
			FVector SpawnLocation = this->GetActorLocation();
			FRotator SpawnRotation(0.0f, 0.0f, 0.0f);
			FActorSpawnParameters SpawnInfo;
			GetWorld()->SpawnActor<AENTPickup>(PickupClass, SpawnLocation, SpawnRotation, SpawnInfo);
		}
	}
	if (GameMode)
	{
		GameMode->EnemyDied();
	}
	Destroy();
}

void AENTEnemy::OnCollisionEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AENTCharacter::StaticClass())) 
	{
		AENTCharacter* charRef = Cast<AENTCharacter>(OtherActor);
		charRef->ReceiveDamage(DamageOutput);
	}
}