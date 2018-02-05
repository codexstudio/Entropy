// Fill out your copyright notice in the Description page of Project Settings.

#include "ENTSharedCamera.h"
#include "Camera/CameraComponent.h"
#include "EngineUtils.h"
#include "ENTCharacter.h"


// Sets default values
AENTSharedCamera::AENTSharedCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
}

// Called when the game starts or when spawned
void AENTSharedCamera::BeginPlay()
{
	Super::BeginPlay();
	for (TActorIterator<AENTCharacter> Itr(GetWorld()); Itr; ++Itr)
	{
		Players.Add(*Itr);
	}
}

void AENTSharedCamera::CalcCameraPosition()
{
	FVector CameraLoc;
	for (const AActor* Player : Players)
	{
		CameraLoc += Player->GetActorLocation();
	}
	
	CameraLoc /= Players.Num();
	CameraLoc.Z = CameraHeight;
	SetActorLocation(CameraLoc);
}

// Called every frame
void AENTSharedCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

