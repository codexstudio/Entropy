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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual ENTCharacterClass GetCharacterClass() const PURE_VIRTUAL(AENTCharacter::GetCharacterClass, return ENTCharacterClass::NONE; );

public:

	//Stat Getters
	FORCEINLINE int GetCurrentHealth() { return CurrHealth; }
	FORCEINLINE int GetStartHealth() { return StartHealth; }
	FORCEINLINE float GetCurrentMovementSpeed() { return CurrMovementSpeed; }
	FORCEINLINE float GetStartMovementSpeed() { return StartMovementSpeed; }
	FORCEINLINE float GetMaxMovementSpeed() { return MaxMovementSpeed; }
	FORCEINLINE float GetCurrentBasicDamage() { return CurrBasicDamage; }
	FORCEINLINE float GetStartBasicDamage() { return StartBasicDamage; }
	FORCEINLINE float GetCurrentBasicROF() { return CurrBasicROF; }
	FORCEINLINE float GetStartBasicROF() { return StartBasicROF; }
	FORCEINLINE float GetMaxBasicROF() { return MaxBasicROF; }
	FORCEINLINE float GetCurrentKnockBack() { return CurrKnockBack; }
	FORCEINLINE float GetStartKnockBack() { return StartKnockBack; }
	FORCEINLINE float GetMaxKnockBack() { return MaxKnockBack; }

protected:
	//Health
	UPROPERTY(BlueprintReadOnly)
	int CurrHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
	int StartHealth;

	UPROPERTY(BlueprintReadOnly)
	float CurrMovementSpeed;

	//Movement Speed
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

private:

};
