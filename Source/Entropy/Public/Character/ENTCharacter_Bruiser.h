// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ENTCharacter.h"
#include "ENTCharacter_Bruiser.generated.h"

/**
 * 
 */
UCLASS()
class ENTROPY_API AENTCharacter_Bruiser : public AENTCharacter
{
	GENERATED_BODY()
	
public:
	AENTCharacter_Bruiser();

	virtual void Tick(float DeltaTime) override;

	FORCEINLINE virtual ENTCharacterClass GetCharacterClass() const override { return ENTCharacterClass::Bruiser; }

protected:
	virtual void BeginPlay() override;
	
	
};
