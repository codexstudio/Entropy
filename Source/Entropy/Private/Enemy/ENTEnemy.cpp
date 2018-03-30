// Fill out your copyright notice in the Description page of Project Settings.

#include "ENTEnemy.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "PaperSpriteComponent.h"
#include "ENTCharacter.h"


// Sets default values
AENTEnemy::AENTEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("Box Component");
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	BoxComponent->SetBoxExtent(FVector(600.0f, 600.0f, 1000.0f));
	RootComponent = BoxComponent;

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>("Sprite Component");
	SpriteComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	SpriteComponent->SetupAttachment(RootComponent);

	FPMovComponent = CreateDefaultSubobject<UFloatingPawnMovement>("Floating Pawn Movement");
	FPMovComponent->MaxSpeed = 600.0f;
	FPMovComponent->Acceleration = 1000.0f;
	FPMovComponent->Deceleration = 2000.0f;
	FPMovComponent->TurningBoost = 8.0f;

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AENTEnemy::OnCollisionEnter);
}

// Called when the game starts or when spawned
void AENTEnemy::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->SetRelativeScale3D(FVector(0.25, 0.25, 0.25));
	SpriteComponent->SetRelativeRotation(FRotator(0, -90, 90));
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

void AENTEnemy::OnCollisionEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AENTCharacter::StaticClass())) {
		AENTCharacter* charRef = Cast<AENTCharacter>(OtherActor);
		UKismetSystemLibrary::PrintString(this, "Enemy hit ");
		charRef->ReceiveDamage(DamageOutput);
	}
}

