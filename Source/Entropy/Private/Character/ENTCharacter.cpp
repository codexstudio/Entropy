// Fill out your copyright notice in the Description page of Project Settings.

#include "ENTCharacter.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "PaperSpriteComponent.h" 
#include "Engine.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ENTPlayerController.h"
#include "EntropyGameModeBase.h"
#include "ENTSharedCamera.h"
#include "ENTProjectile.h"
#include "WidgetComponent.h"
#include "HealthWidget.h"
#include "Sound/SoundCue.h"

// Sets default values
AENTCharacter::AENTCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("Floating Pawn Movement");

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>("Sprite Component");
	RootComponent = SpriteComponent;
	RootComponent->RelativeRotation = FRotator(0.0f, 90.0f, -90.0f);

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>("Projectile Spawn Point");
	ArrowComponent->SetupAttachment(RootComponent);
	ArrowComponent->RelativeRotation = (FRotator(90.0f, 0.0f, 90.0f));
	ArrowComponent->RelativeLocation = (FVector(0.0f, 0.0f, 250.0f));
	
	HealthWidgetComp = CreateDefaultSubobject<UWidgetComponent>("Health Widget");
	HealthWidgetComp->bGenerateOverlapEvents = false;
	HealthWidgetComp->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	
	HealthWidgetComp->SetupAttachment(RootComponent);
	HealthWidgetComp->RelativeRotation = FRotator(90.0f, 0.0f, 180.0f);
	HealthWidgetComp->RelativeLocation = FVector(0.0f, 20.0f, 0.0f);

	DamageAudioComponent = CreateDefaultSubobject<UAudioComponent>("Damage Audio Component");
	DamageAudioComponent->bAutoActivate = false;
	DamageAudioComponent->SetupAttachment(RootComponent);

	DeathAudioComponent = CreateDefaultSubobject<UAudioComponent>("Death Audio Component");
	DeathAudioComponent->bAutoActivate = false;
	DeathAudioComponent->SetupAttachment(RootComponent);

	RespawnAudioComponent = CreateDefaultSubobject<UAudioComponent>("Respawn Audio Component");
	RespawnAudioComponent->bAutoActivate = false;
	RespawnAudioComponent->SetupAttachment(RootComponent);

	ShootingAudioComponent = CreateDefaultSubobject<UAudioComponent>("Shooting Audio Component");
	ShootingAudioComponent->bAutoActivate = false;
	ShootingAudioComponent->SetupAttachment(RootComponent);

	PickupAudioComponent = CreateDefaultSubobject<UAudioComponent>("Pickup Audio Component");
	PickupAudioComponent->bAutoActivate = false;
	PickupAudioComponent->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<USoundCue> DamageCue
	{
		TEXT("'/Game/Sound/Real_Sounds/Sound_Cues/Player_Hit_Sound_Cue.Player_Hit_Sound_Cue'")
	};

	static ConstructorHelpers::FObjectFinder<USoundCue> DeathCue
	{
		TEXT("'/Game/Sound/Real_Sounds/Sound_Cues/Player_Death_Sound_Cue.Player_Death_Sound_Cue'")
	};

	static ConstructorHelpers::FObjectFinder<USoundCue> RespawnCue
	{
		TEXT("'/Game/Sound/Real_Sounds/Sound_Cues/Player_Revive_Sound_Cue.Player_Revive_Sound_Cue'")
	};

	static ConstructorHelpers::FObjectFinder<USoundCue> ShootingCue
	{
		TEXT("'/Game/Sound/Real_Sounds/Sound_Cues/Shooting_Sound_Cue.Shooting_Sound_Cue'")
	};

	static ConstructorHelpers::FObjectFinder<USoundCue> PickupCue
	{
		TEXT("'/Game/Sound/Real_Sounds/Sound_Cues/Pickup_Sound_Cue.Pickup_Sound_Cue'")
	};

	DamageSoundCue = DamageCue.Object;
	DeathSoundCue = DeathCue.Object;
	RespawnSoundCue = RespawnCue.Object;
	ShootingSoundCue = ShootingCue.Object;
	PickupSoundCue = PickupCue.Object;
}

void AENTCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	HealthWidgetComp->SetWidgetClass(HealthWidgetClass);
	HealthWidgetComp->SetAbsolute(false, true, true);

	if (DamageSoundCue->IsValidLowLevelFast())
	{
		DamageAudioComponent->SetSound(DamageSoundCue);
	}
	if (DeathSoundCue->IsValidLowLevelFast())
	{
		DeathAudioComponent->SetSound(DeathSoundCue);
	}
	if (RespawnSoundCue->IsValidLowLevelFast())
	{
		RespawnAudioComponent->SetSound(RespawnSoundCue);
	}
	if (ShootingSoundCue->IsValidLowLevelFast())
	{
		ShootingAudioComponent->SetSound(ShootingSoundCue);
	}
	if (PickupSoundCue->IsValidLowLevelFast())
	{
		PickupAudioComponent->SetSound(PickupSoundCue);
	}
}

// Called when the game starts or when spawned
void AENTCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Assign current stats
	CurrHealth = StartHealth;
	CurrMovementSpeed = StartMovementSpeed;
	MyPawnMovement->MaxSpeed = CurrMovementSpeed;
	CurrBasicDamage = StartBasicDamage;
	CurrBasicROF = StartBasicROF;
	CurrKnockBack = StartKnockBack;

	if (UHealthWidget* HW = Cast<UHealthWidget>(HealthWidgetComp->GetUserWidgetObject()))
	{
		HW->InitWidget();
		HW->RepresentHealth(CurrHealth);
	}

	OnControllerConnectionHandle = FCoreDelegates::OnControllerConnectionChange.AddUFunction(this, FName("OnControllerConnectionChange"));
}

void AENTCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	FCoreDelegates::OnControllerConnectionChange.Remove(OnControllerConnectionHandle);
}

void AENTCharacter::OnControllerConnectionChange_Implementation(bool Connected, int32 UserID, int32 ControllerID)
{
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Connection change id: x: %d, connected: %s"), ControllerID, (Connected ? TEXT("true") : TEXT("false"))));
}

// Called every frame
void AENTCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AENTCharacter::ApplyPickup(ENTCharacterClass PickupClass)
{
	PickupAudioComponent->Play();
	AddToCurrHealth((GetCharacterClass() == ENTCharacterClass::Tank && PickupClass == GetCharacterClass()) ? (int)SpecializedStatIncrement : BaseHealthIncrement);
	AddToCurrMovementSpeed((GetCharacterClass() == ENTCharacterClass::Assassin && PickupClass == GetCharacterClass()) ? SpecializedStatIncrement : BaseMovSpeedIncrement);
	AddToCurrBasicDamage(BaseDamageIncrement);
	AddToCurrBasicROF((GetCharacterClass() == ENTCharacterClass::ADC && PickupClass == GetCharacterClass()) ? SpecializedStatIncrement : BaseROFIncrement);
	AddToCurrKnockBack((GetCharacterClass() == ENTCharacterClass::Bruiser && PickupClass == GetCharacterClass()) ? SpecializedStatIncrement : BaseKnockBackIncrement);
}

void AENTCharacter::ReceiveDamage(uint32 Dmg)
{
	if (Vulnerable) 
	{
		//UKismetSystemLibrary::PrintString(this, "Damage Taken. Health :" + FString::FromInt(CurrHealth - Dmg));
		if ((CurrHealth - Dmg) <= 0 && !bIsDead)
		{
			UKismetSystemLibrary::PrintString(this, "Health reduced below 0");
			Die();
		}
		else
		{
			CurrHealth -= Dmg;
		}

		if (UHealthWidget* HW = Cast<UHealthWidget>(HealthWidgetComp->GetUserWidgetObject()))
		{
			HW->RepresentHealth(CurrHealth);
		}
		DamageAudioComponent->Play();
	}
}

void AENTCharacter::Die()
{
	bIsDead = true;
	AEntropyGameModeBase* const GM = (GetWorld() != nullptr) ? GetWorld()->GetAuthGameMode<AEntropyGameModeBase>() : nullptr;
	if (GM)
	{
		UKismetSystemLibrary::PrintString(this, "Calling check loss condition");
		if (GM->CheckLossCondition()) { return; }
	}
	DeathAudioComponent->Play();
	StopBaseAttack();
	SetVulnerability(false);
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
	Cast<AENTPlayerController>(GetController())->DisableController();
	GetWorld()->GetTimerManager().SetTimer(DeathHandle, this, &AENTCharacter::Respawn, DeathTimer, false);
}

void AENTCharacter::Respawn()
{
	bIsDead = false;
	CurrHealth = StartHealth;
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetActorTickEnabled(true);
	FVector CamLoc;
	AEntropyGameModeBase* const GM = (GetWorld() != nullptr) ? GetWorld()->GetAuthGameMode<AEntropyGameModeBase>() : nullptr;
	if (GM)
	{
		CamLoc = GM->GetSharedCamera()->GetActorLocation();
	}
	SetActorLocation(FVector(CamLoc.X, CamLoc.Y, 0.0f));
	Cast<AENTPlayerController>(GetController())->EnableController();
	RespawnAudioComponent->Play();
	GetWorld()->GetTimerManager().SetTimer(InvulnerableFlickerHandle, this, &AENTCharacter::ToggleSprite, InvulnerableFlickerRate, true);
	GetWorld()->GetTimerManager().SetTimer(InvulnerableHanlde, this, &AENTCharacter::ComeOutOfInvulnerability, InvulnerableTimer, false);
	if (UHealthWidget* HW = Cast<UHealthWidget>(HealthWidgetComp->GetUserWidgetObject()))
	{
		HW->RepresentHealth(CurrHealth);
	}
}

void AENTCharacter::ComeOutOfInvulnerability()
{
	GetWorldTimerManager().ClearTimer(InvulnerableFlickerHandle);
	SpriteComponent->SetVisibility(true);
	SetVulnerability(true);
}

void AENTCharacter::SetVulnerability(bool value)
{
	Vulnerable = value;
}

void AENTCharacter::ToggleSprite()
{
	SpriteComponent->SetVisibility(!SpriteComponent->IsVisible());
}


void AENTCharacter::StartBaseAttack()
{
	if (!GetWorldTimerManager().IsTimerActive(BaseAttackHandle) && bCanShoot)
	{
		GetWorld()->GetTimerManager().SetTimer(BaseAttackHandle, this, &AENTCharacter::FireBaseAttack, 1 / CurrBasicROF, true, 0);
		bIsShooting = true;
	}
}

void AENTCharacter::StopBaseAttack()
{
	if (GetWorld())
	{
		GetWorldTimerManager().ClearTimer(BaseAttackHandle);
		if (bIsShooting)
		{
			bCanShoot = false;
			GetWorld()->GetTimerManager().SetTimer(BaseAttackCoodown, this, &AENTCharacter::ResetShootCooldown, 1 / CurrBasicROF, false);
		}

		bIsShooting = false;
	}
}

void AENTCharacter::ResetShootCooldown()
{
	bCanShoot = true;
}

void AENTCharacter::FireBaseAttack()
{
	const FVector SpawnLocation = ArrowComponent->GetComponentLocation();
	const FRotator SpawnRotation = ArrowComponent->GetComponentRotation();
	const FTransform SpawnTransform = FTransform(SpawnRotation, SpawnLocation);
	AENTProjectile* ProjectileActor = GetWorld()->SpawnActorDeferred<AENTProjectile>(Projectile, SpawnTransform);
	ProjectileActor->SpawnSetup(ENTProjectileType::PlayerProjectile, CurrBasicDamage, CurrKnockBack);
	ProjectileActor->FinishSpawning(SpawnTransform);
	ShootingAudioComponent->Play();
}

void AENTCharacter::UseSpecial()
{
	if (!bIsUsingSpecial && bIsSpecialReady)
	{
		bIsUsingSpecial = true;
		bIsSpecialReady = false;

		StartSpecialAttack();

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
	if (UHealthWidget* HW = Cast<UHealthWidget>(HealthWidgetComp->GetUserWidgetObject()))
	{
		HW->RepresentHealth(CurrHealth);
	}
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


