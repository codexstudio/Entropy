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
#include "BehaviorTree/BlackboardComponent.h"

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
	FPMovComponent->MaxSpeed = StartSpeed;
	FPMovComponent->Acceleration = 10000000.0f;
	FPMovComponent->Deceleration = 0.0f;
	FPMovComponent->TurningBoost = 8.0f;

	DeathAudioComponent = CreateDefaultSubobject<UAudioComponent>("Death Audio Component");
	DeathAudioComponent->bAutoActivate = false;
	DeathAudioComponent->SetupAttachment(RootComponent);

	TakeDamageAudioComponent = CreateDefaultSubobject<UAudioComponent>("Take Damage Audio Component");
	TakeDamageAudioComponent->bAutoActivate = false;
	TakeDamageAudioComponent->SetupAttachment(RootComponent);

	ShootingAudioComponent = CreateDefaultSubobject<UAudioComponent>("Shooting Audio Component");
	ShootingAudioComponent->bAutoActivate = false;
	ShootingAudioComponent->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<USoundCue> DeathCue
	{
		TEXT("'/Game/Sound/Real_Sounds/Sound_Cues/Enemy_Death_Sound_Cue.Enemy_Death_Sound_Cue'")
	};

	static ConstructorHelpers::FObjectFinder<USoundCue> DamageCue
	{
		TEXT("'/Game/Sound/Real_Sounds/Sound_Cues/Enemy_Hit_Sound_Cue.Enemy_Hit_Sound_Cue'")
	};

	static ConstructorHelpers::FObjectFinder<USoundCue> ShootingCue
	{
		TEXT("'/Game/Sound/Real_Sounds/Sound_Cues/Shooting_Sound_2_Cue.Shooting_Sound_2_Cue'")
	};

	DeathSoundCue = DeathCue.Object;
	TakeDamageSoundCue = DamageCue.Object;
	ShootingSoundCue = ShootingCue.Object;

	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AENTEnemy::OnCollisionEnter);
}

void AENTEnemy::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (DeathSoundCue->IsValidLowLevelFast())
	{
		DeathAudioComponent->SetSound(DeathSoundCue);
	}
	if (TakeDamageSoundCue->IsValidLowLevelFast())
	{
		TakeDamageAudioComponent->SetSound(TakeDamageSoundCue);
	}
	if (ShootingSoundCue->IsValidLowLevelFast())
	{
		ShootingAudioComponent->SetSound(ShootingSoundCue);
	}
}

void AENTEnemy::SpawnSetup(float HealthInjection, int DamageInjection, float SpeedInjection)
{
	StartHealth += HealthInjection;
	DamageOutput += DamageInjection;
	BonusSpeed = SpeedInjection;
}

// Called when the game starts or when spawned
void AENTEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	CurrHealth = StartHealth;
	if (StartSpeed + BonusSpeed <= TopSpeed)
	{
		FPMovComponent->MaxSpeed = StartSpeed + BonusSpeed;
	}
	else
	{
		FPMovComponent->MaxSpeed = TopSpeed;
	}

	GameMode = (GetWorld() != nullptr) ? GetWorld()->GetAuthGameMode<AEntropyGameModeBase>() : nullptr;

	float RandNum = FMath::RandRange(0.0f, 100.0f);
	if ((RandNum <= ChanceToGoRetard))
	{
		if (GetController())
		{
			AENTAIController* AICon = Cast<AENTAIController>(GetController());
			if (AICon && GameMode)
			{
				AICon->GetBlackboardComponent()->SetValueAsBool("Disabled", true);
				//UKismetSystemLibrary::PrintString(this, "Speed :" + FString::SanitizeFloat(FPMovComponent->GetMaxSpeed()));
				FVector Dir = GameMode->GetSharedCamera()->GetActorLocation() - GetActorLocation();
				Dir.Normalize();
				FPMovComponent->Velocity = Dir * FPMovComponent->GetMaxSpeed();
			}
		}
	}
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

void AENTEnemy::ReceiveDamage(float Dmg, float KnockBackAmount, FVector KnockbackDirection, AENTCharacter* Attacker)
{
	if ((CurrHealth - Dmg) <= 0.0f)
	{
		Die();
	}
	else 
	{
		TakeDamageAudioComponent->Play();
		CurrHealth -= Dmg;
		FPMovComponent->Velocity = FVector(0.0f, 0.0f, 0.0f);
		ToggleStunned();
		if (AENTAIController* AICon = Cast<AENTAIController>(GetController()))
		{
			AICon->SetLastAttacker(Attacker);
			AICon->GetBlackboardComponent()->SetValueAsBool("Disabled", false);
		}
		GetWorld()->GetTimerManager().SetTimer(StunHandle, this, &AENTEnemy::ToggleStunned, KnockBackAmount / 100, false);
	}
}

void AENTEnemy::ToggleStunned()
{
	if (AENTAIController* AICon = Cast<AENTAIController>(GetController()))
	{
		AICon->SetIsStunned(!AICon->GetIsStunned());
		if (AICon->GetIsStunned())
		{
			FPMovComponent->MaxSpeed = 0.0f;
		} 
		else
		{
			if (StartSpeed + BonusSpeed <= TopSpeed)
			{
				FPMovComponent->MaxSpeed = StartSpeed + BonusSpeed;
			}
			else
			{
				FPMovComponent->MaxSpeed = TopSpeed;
			}
		}
	}
}

void AENTEnemy::DelayedDestroy()
{
	Destroy();
}

void AENTEnemy::Die(bool DiedToPlayer)
{
	if (GameMode)
	{
		GameMode->EnemyDied(DiedToPlayer);
	}
	if (DiedToPlayer)
	{
		DeathAudioComponent->Play();
		float RandNum = FMath::RandRange(0.0f, 100.0f);
		if (RandNum <= ChanceToDropPickup)
		{
			FVector SpawnLocation = this->GetActorLocation();
			FRotator SpawnRotation(0.0f, 0.0f, 0.0f);
			FActorSpawnParameters SpawnInfo;
			GetWorld()->SpawnActor<AENTPickup>(PickupClass, SpawnLocation, SpawnRotation, SpawnInfo);
		}
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
		GetWorld()->GetTimerManager().SetTimer(DeathHandle, this, &AENTEnemy::DelayedDestroy, DeathSoundCue->GetDuration(), false);
	}
	else
	{
		Destroy();
	}
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