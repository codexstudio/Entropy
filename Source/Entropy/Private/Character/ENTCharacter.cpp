// Fill out your copyright notice in the Description page of Project Settings.

#include "ENTCharacter.h"
#include "Runtime/Engine/Classes/GameFramework/FloatingPawnMovement.h"



// Sets default values
AENTCharacter::AENTCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MyPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("Floating Pawn Movement");
}

// Called when the game starts or when spawned
void AENTCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AENTCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}