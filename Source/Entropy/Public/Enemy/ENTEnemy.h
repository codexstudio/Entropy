// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ENTEnemy.generated.h"

UCLASS()
class ENTROPY_API AENTEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AENTEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SpawnSetup(float HealthInjection, int DamageInjection, float SpeedInjection);

	void ReceiveDamage(float Dmg, float KnockBackAmount, FVector KnockbackDirection, class AENTCharacter* Attacker = nullptr);

protected:
	UFUNCTION()
	void OnCollisionEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void Die(bool DiedToPlayer = true);

	void ToggleStunned();

	void DelayedDestroy();
	
protected:
	UPROPERTY(BlueprintReadOnly)
	float CurrHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
	float StartHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
	float StartSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
	float TopSpeed;

	float BonusSpeed = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
	int DamageOutput;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
	float ChanceToDropPickup;

	const float MaxDistanceFromCamera = 20000.0f;

	FTimerHandle StunHandle;
	FTimerHandle DeathHandle;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AENTPickup> PickupClass;

	UPROPERTY(VisibleAnywhere)
	class UFloatingPawnMovement* FPMovComponent;

	UPROPERTY(VisibleAnywhere)
	class UPaperSpriteComponent* SpriteComponent;

	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* CapsuleComponent;

	class AEntropyGameModeBase* GameMode;
	
	//Sounds
	class UAudioComponent* DeathAudioComponent;
	class USoundCue* DeathSoundCue;

	class UAudioComponent* TakeDamageAudioComponent;
	class USoundCue* TakeDamageSoundCue;

	class UAudioComponent* ShootingAudioComponent;
	class USoundCue* ShootingSoundCue;
};
