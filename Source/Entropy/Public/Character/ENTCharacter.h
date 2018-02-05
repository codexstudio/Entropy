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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual ENTCharacterClass GetCharacterClass() const PURE_VIRTUAL(AENTCharacter::GetCharacterClass, return ENTCharacterClass::NONE; );


	FORCEINLINE int GetCurrentHealth() { return CurrHealth; }
	FORCEINLINE int GetStartHealth() { return StartHealth; }
	FORCEINLINE float GetCurrentMovementSpeed() { return CurrMovementSpeed; }
	FORCEINLINE float GetStartMovementSpeed() { return StartMovementSpeed; }
	FORCEINLINE float GetMaxMovementSpeed() { return MaxMovementSpeed; }

public:

protected:
	UPROPERTY(BlueprintReadOnly)
	int CurrHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
	int StartHealth;

	UPROPERTY(BlueprintReadOnly)
	float CurrMovementSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
	float StartMovementSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
	float MaxMovementSpeed;

private:
	

};
