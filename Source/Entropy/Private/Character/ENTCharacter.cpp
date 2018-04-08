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
#include "Image.h"

// Sets default values
AENTCharacter::AENTCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("Floating Pawn Movement");
	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>("Sprite Component");
	RootComponent = SpriteComponent;

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>("Projectile Spawn Point");
	ArrowComponent->SetupAttachment(RootComponent);
	
	HealthWidgetComp = CreateDefaultSubobject<UWidgetComponent>("Health Widget");
	HealthWidgetComp->SetupAttachment(RootComponent);
}

void AENTCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SetActorRotation(FRotator(0.0f, -90.0f, 90.0f));

	ArrowComponent->SetRelativeRotation(FRotator(90.0f, 0.0f, 90.0f));
	ArrowComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 250.0f));

	HealthWidgetComp->SetWidgetClass(HealthWidgetClass);
	HealthWidgetComp->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	HealthWidgetComp->SetRelativeLocation(FVector(0.0f, -1.0f, 0.0f));
	HealthWidgetComp->SetDrawSize(FVector2D(100.0f, 100.0f));

	//Illegal cast. Dont Use, will crash
	//Cast<UHealthWidget>(HealthWidgetClass)->GetImage()->GetDynamicMaterial()->SetScalarParameterValue("Alpha", CurrHealth / 4);
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

	//UImage::GetDynamicMaterial()->SetScalarParameterValue("Alpha", CurrHealth / 5);
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

void AENTCharacter::ReceiveDamage(uint32 Dmg)
{
	if (Vulnerable) 
	{
		UKismetSystemLibrary::PrintString(this, "Damage Taken. Health :" + FString::FromInt(CurrHealth - Dmg));
		if ((CurrHealth - Dmg) <= 0)
		{
			Die();
		}
		else
		{
			CurrHealth -= Dmg;
		}
	}
}

void AENTCharacter::Die()
{
	IsPlayerAlive();
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
	IsAliveAgain();
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
	GetWorld()->GetTimerManager().SetTimer(InvulnerableFlickerHandle, this, &AENTCharacter::ToggleSprite, InvulnerableFlickerRate, true);
	GetWorld()->GetTimerManager().SetTimer(InvulnerableHanlde, this, &AENTCharacter::ComeOutOfInvulnerability, InvulnerableTimer, false);
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
	bool SpriteVisible = SpriteComponent->IsVisible();
	SpriteComponent->SetVisibility(!SpriteVisible);
}

void AENTCharacter::StartBaseAttack()
{
	if (!GetWorldTimerManager().IsTimerActive(BaseAttackHandle))
	{
		GetWorld()->GetTimerManager().SetTimer(BaseAttackHandle, this, &AENTCharacter::FireBaseAttack, 1 / CurrBasicROF, true);
	}
}

void AENTCharacter::StopBaseAttack()
{
	GetWorldTimerManager().ClearTimer(BaseAttackHandle);
}

void AENTCharacter::FireBaseAttack()
{
	const FVector SpawnLocation = ArrowComponent->GetComponentLocation();
	const FRotator SpawnRotation = ArrowComponent->GetComponentRotation();
	const FTransform SpawnTransform = FTransform(SpawnRotation, SpawnLocation);
	AENTProjectile* ProjectileActor = GetWorld()->SpawnActorDeferred<AENTProjectile>(Projectile, SpawnTransform);
	ProjectileActor->SpawnSetup(ENTProjectileType::PlayerProjectile, CurrBasicDamage);
	ProjectileActor->FinishSpawning(SpawnTransform);
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


