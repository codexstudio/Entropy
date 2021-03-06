// Fill out your copyright notice in the Description page of Project Settings.

#include "ENTSharedCamera.h"
#include "Camera/CameraComponent.h"
#include "EngineUtils.h"
#include "ENTCharacter.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
AENTSharedCamera::AENTSharedCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = RootComp;

	CameraBoomComp = CreateDefaultSubobject<USpringArmComponent>("Camera Boom");
	CameraBoomComp->SetupAttachment(RootComp);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComp->SetupAttachment(CameraBoomComp, USpringArmComponent::SocketName);
}

float AENTSharedCamera::GetOrthoWidth() const
{
	return CameraComp->OrthoWidth;
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

FVector AENTSharedCamera::CalcCameraPosition()
{
	FVector CameraLoc(ForceInitToZero);
	int PlayersAlive = 0;
	for (AActor* Player : Players)
	{
		AENTCharacter* CharRef = Cast<AENTCharacter>(Player);
		if (CharRef)
		{
			if (!CharRef->IsDead())
			{
				PlayersAlive++;
				CameraLoc += Player->GetActorLocation();
			}
		}
	}
	
	CameraLoc /= PlayersAlive;
	return CameraLoc;
}

// Called every frame
void AENTSharedCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(CalcCameraPosition());
}