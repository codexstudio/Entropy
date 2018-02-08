// Fill out your copyright notice in the Description page of Project Settings.

#include "ENTPickup.h"


// Sets default values
AENTPickup::AENTPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetRandomPickupClass();
}

// Called when the game starts or when spawned
void AENTPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AENTPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AENTPickup::SetPickupClass(ENTCharacterClass ENTClass)
{
	PickupClass = ENTClass;
	//Set Sprite
}

void AENTPickup::SetRandomPickupClass()
{
	SetPickupClass((ENTCharacterClass) FMath::RandRange(0, 3));
}