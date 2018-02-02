// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ENTCharacter.h"
#include "ENTCharacter_Assassin.generated.h"

/**
 * 
 */
UCLASS()
class ENTROPY_API AENTCharacter_Assassin : public AENTCharacter
{
	GENERATED_BODY()
	
public:
	AENTCharacter_Assassin();

	virtual void Tick(float DeltaTime) override;

	FORCEINLINE virtual ENTCharacterClass GetCharacterClass() const override { return ENTCharacterClass::Assassin; }

protected:
	virtual void BeginPlay() override;
	
	
	
};
