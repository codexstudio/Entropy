// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ENTCharacter.h"
#include "ENTCharacter_Tank.generated.h"

/**
 * 
 */
UCLASS()
class ENTROPY_API AENTCharacter_Tank : public AENTCharacter
{
	GENERATED_BODY()

		AENTCharacter_Tank();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE virtual ENTCharacterClass GetCharacterClass() const override { return ENTCharacterClass::Tank; }
};
