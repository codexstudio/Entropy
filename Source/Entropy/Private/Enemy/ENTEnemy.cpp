// Fill out your copyright notice in the Description page of Project Settings.

#include "ENTEnemy.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "PaperSpriteComponent.h"
#include "ENTCharacter.h"
#include "UnrealMathUtility.h"
#include "EntropyGameModeBase.h"
#include "ENTSharedCamera.h"
#include "ENTPickup.h"
#include "Components/CapsuleComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "ConstructorHelpers.h"
#include "ENTAIController.h"

// Sets default values
AENTEnemy::AENTEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("Capsule Component");
	CapsuleComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	RootComponent = CapsuleComponent;
	CapsuleComponent->SetCapsuleSize(600.0f, 1000.0f);
	CapsuleComponent->RelativeScale3D = (FVector(0.25, 0.25, 0.25));
	
	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>("Sprite Component");
	SpriteComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	SpriteComponent->SetupAttachment(RootComponent);
	SpriteComponent->RelativeRotation = (FRotator(0, -90, 90));

	FPMovComponent = CreateDefaultSubobject<UFloatingPawnMovement>("Floating Pawn Movement");
	FPMovComponent->MaxSpeed = 600.0f;
	FPMovComponent->Acceleration = 10000000.0f;
	FPMovComponent->Deceleration = 0.0f;
	FPMovComponent->TurningBoost = 8.0f;

	DeathAudioComponent = CreateDefaultSubobject<UAudioComponent>("Death Audio Component");
	DeathAudioComponent->bAutoActivate = false;
	DeathAudioComponent->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<USoundCue> DeathCue
	{
		TEXT("'/Game/Sound/SoundCue_EnemyDeath.SoundCue_EnemyDeath'")
	};

	DeathSoundCue = DeathCue.Object;

	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AENTEnemy::OnCollisionEnter);
}

void AENTEnemy::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (DeathSoundCue->IsValidLowLevelFast())
	{
		DeathAudioComponent->SetSound(DeathSoundCue);
	}

	//DeathAudioComponent->OnAudioFinishedNative.AddDynamic(this, &APawn::Destroy());
	//DeathAudioComponent->OnAudioFinishedNative.AddUFunction(this, &AENTEnemy::Destroy());
}

void AENTEnemy::SpawnSetup(float HealthInjection, int DamageInjection)
{
	StartHealth += HealthInjection;
	DamageOutput += DamageInjection;
}

// Called when the game starts or when spawned
void AENTEnemy::BeginPlay()
{
	Super::BeginPlay();
	
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

void AENTEnemy::ReceiveDamage(float Dmg, float KnockBackAmount, FVector KnockbackDirection)
{
	UKismetSystemLibrary::PrintString(this, "Enemy Taking Fire!!!");
	if ((CurrHealth - Dmg) <= 0) 
	{
		Die();
	}
	else 
	{
		CurrHealth -= Dmg;
		ToggleStunned();
		FVector KnockBackNorm = (KnockbackDirection.GetSafeNormal());
		FVector KnockBack = KnockBackNorm * KnockBackAmount;
		//UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("KnockbackAmount: %f"), KnockBackAmount));
		//UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("KnockbackSize: %f"), KnockBack.Size()));
		FPMovComponent->Velocity = KnockBack;
		GetWorld()->GetTimerManager().SetTimer(StunHandle, this, &AENTEnemy::ToggleStunned, StunTimer, false);
	}
}

void AENTEnemy::ToggleStunned()
{
	if (AENTAIController* AICon = Cast<AENTAIController>(GetController()))
	{
		if (AICon->GetIsStunned())
		{
			FPMovComponent->MaxSpeed = 600.0f;
		} 
		else
		{
			FPMovComponent->MaxSpeed = 20000.0f;
		}
		AICon->SetIsStunned(!AICon->GetIsStunned());
	}
}

void AENTEnemy::Die(bool DiedToPlayer)
{
	if (DiedToPlayer)
	{
		//DeathAudioComponent->Play();
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
		GameMode->EnemyDied(DiedToPlayer);
	}
	Destroy();
}

void AENTEnemy::OnCollisionEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AENTCharacter::StaticClass()))
	{
		AENTCharacter* CharRef = Cast<AENTCharacter>(OtherActor);
		if (CharRef)
		{
			CharRef->ReceiveDamage(DamageOutput);
		}
	}
}