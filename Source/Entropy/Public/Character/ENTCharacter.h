// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ENTCharacterEnums.h"
#include "ENTCharacter.generated.h"

UCLASS(abstract)
class ENTROPY_API AENTCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AENTCharacter();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class UFloatingPawnMovement* MyPawnMovement;

	UPROPERTY(VisibleAnywhere)
	class UPaperSpriteComponent* SpriteComponent;

	UPROPERTY(VisibleAnywhere)
	class UArrowComponent* ArrowComponent;

	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* HealthWidgetComp;

	class UAudioComponent* DamageAudioComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

	virtual ENTCharacterClass GetCharacterClass() const PURE_VIRTUAL(AENTCharacter::GetCharacterClass, return ENTCharacterClass::NONE; );

public:
	//Stat Getters
	FORCEINLINE int GetCurrentHealth() { return CurrHealth; }
	//FORCEINLINE int GetStartHealth() { return StartHealth; }
	FORCEINLINE float GetCurrentMovementSpeed() { return CurrMovementSpeed; }
	//FORCEINLINE float GetStartMovementSpeed() { return StartMovementSpeed; }
	//FORCEINLINE float GetMaxMovementSpeed() { return MaxMovementSpeed; }
	FORCEINLINE float GetCurrentBasicDamage() { return CurrBasicDamage; }
	//FORCEINLINE float GetStartBasicDamage() { return StartBasicDamage; }
	FORCEINLINE float GetCurrentBasicROF() { return CurrBasicROF; }
	//FORCEINLINE float GetStartBasicROF() { return StartBasicROF; }
	//FORCEINLINE float GetMaxBasicROF() { return MaxBasicROF; }
	FORCEINLINE float GetCurrentKnockBack() { return CurrKnockBack; }
	//FORCEINLINE float GetStartKnockBack() { return StartKnockBack; }
	//FORCEINLINE float GetMaxKnockBack() { return MaxKnockBack; }

	//Pickup
	void ApplyPickup(ENTCharacterClass PickupClass);

	//Damage
	void ReceiveDamage(uint32 dmg);

	FORCEINLINE bool IsDead() { return bIsDead; }

protected:
	//Stat Functions
	void AddToCurrHealth(int value);
	void AddToCurrMovementSpeed(float value);
	void AddToCurrBasicDamage(float value);
	void AddToCurrBasicROF(float value);
	void AddToCurrKnockBack(float value);

	void Die();
	void Respawn();
	void ComeOutOfInvulnerability();
	void SetVulnerability(bool value);
	void ToggleSprite();

protected:
	//Health
	UPROPERTY(BlueprintReadOnly)
	int CurrHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
	int StartHealth;

	//Movement Speed
	UPROPERTY(BlueprintReadOnly)
	float CurrMovementSpeed;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
	float StartMovementSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
	float MaxMovementSpeed;

	//Basic Attack Damage
	UPROPERTY(BlueprintReadOnly)
	float CurrBasicDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
	float StartBasicDamage;

	//Basic Rate of Fire
	UPROPERTY(BlueprintReadOnly)
	float CurrBasicROF;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
	float StartBasicROF;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
	float MaxBasicROF;

	//Knock back Amount
	UPROPERTY(BlueprintReadOnly)
	float CurrKnockBack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
	float StartKnockBack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
	float MaxKnockBack;

protected:
	bool bIsDead = false;
	bool Vulnerable = true;
	const float DeathTimer = 5.0f;
	const float InvulnerableTimer = 3.0f;
	const float InvulnerableFlickerRate = 0.2f;
	FTimerHandle DeathHandle;
	FTimerHandle InvulnerableHanlde;
	FTimerHandle InvulnerableFlickerHandle;

	//Stat Increments
	const int BaseHealthIncrement = 1;
	const float BaseMovSpeedIncrement = 100.0f;
	const float BaseDamageIncrement = 0.2f;
	const float BaseROFIncrement = 0.1f;
	const float BaseKnockBackIncrement = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
	float SpecializedStatIncrement;

public:
	//Special Skill
	FTimerHandle SpecialCooldownHandle;

	FTimerHandle SpecialIntervalHandle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Special Skill")
	float SpecialCooldown;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Special Skill")
	float SpecialInterval;

	bool bIsSpecialReady;

	bool bIsUsingSpecial;

	virtual void UseSpecial();

	virtual void ResetSpecialCooldown();

	virtual void StopSpecial();

	virtual void StartSpecialAttack() {}

//Base Attack
public:
	void StartBaseAttack();
	void StopBaseAttack();

protected:

	void FireBaseAttack();
	FTimerHandle BaseAttackHandle;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<class AENTProjectile> Projectile;

	UPROPERTY(EditDefaultsOnly, Category = "Health Widget")
	TSubclassOf<class UUserWidget> HealthWidgetClass;

protected:
	class USoundCue* DamageSoundCue;
};

