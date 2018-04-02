// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ENTCharacter.h"
#include "ENTCharacter_ADC.generated.h"

/**
 * 
 */
UCLASS()
class ENTROPY_API AENTCharacter_ADC : public AENTCharacter
{
	GENERATED_BODY()
		
public:
	AENTCharacter_ADC();
	
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE virtual ENTCharacterClass GetCharacterClass() const override { return ENTCharacterClass::ADC; }


//Special Skill Methods
	void SpecialAttack();

	void StartSpecialAttack() override;

protected:
	virtual void BeginPlay() override;

//Special Skill
	UPROPERTY(EditDefaultsOnly, Category = "Special Skill")
	FVector Offset;

	UPROPERTY(EditDefaultsOnly, Category = "Special Skill")
	float AngleAdjuster;

	UPROPERTY(EditDefaultsOnly, Category = "Special Skill")
	int BulletsPerSide;

	UPROPERTY(EditDefaultsOnly, Category = "Special Skill")
	float SpecialROF;

	FTimerHandle SpecialAttackIntervalHandle;
};
