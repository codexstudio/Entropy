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

public:
	AENTCharacter_Tank();

	virtual void Tick(float DeltaTime) override;

	FORCEINLINE virtual ENTCharacterClass GetCharacterClass() const override { return ENTCharacterClass::Tank; }
	
protected:
	virtual void BeginPlay() override;
};
