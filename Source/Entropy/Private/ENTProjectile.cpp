// Fill out your copyright notice in the Description page of Project Settings.

#include "ENTProjectile.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine.h"


// Sets default values
AENTProjectile::AENTProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = PaperSpriteComp;
	PaperSpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>("Paper Sprite Component");

	BoxComp = CreateDefaultSubobject<UBoxComponent>("Box Component");
	BoxComp->SetBoxExtent(FVector::FVector(20.f));
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AENTProjectile::OnOverlap);
	BoxComp->SetupAttachment(RootComponent);

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement Component");
	ProjectileMovementComp->InitialSpeed = 3000.f;
	ProjectileMovementComp->ProjectileGravityScale = 0.0f;
}

// Called when the game starts or when spawned
void AENTProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AENTProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AENTProjectile::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, TEXT("Hit"));
}

