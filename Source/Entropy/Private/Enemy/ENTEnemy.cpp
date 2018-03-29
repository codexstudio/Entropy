// Fill out your copyright notice in the Description page of Project Settings.

#include "ENTEnemy.h"


// Sets default values
AENTEnemy::AENTEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AENTEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AENTEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AENTEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

