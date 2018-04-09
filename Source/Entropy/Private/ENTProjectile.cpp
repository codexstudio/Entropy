// Fill out your copyright notice in the Description page of Project Settings.

#include "ENTProjectile.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ENTEnemy.h"
#include "ENTCharacter.h"
#include "ENTCharacterEnums.h"


// Sets default values
AENTProjectile::AENTProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = BoxComp;
	BoxComp = CreateDefaultSubobject<UBoxComponent>("Box Component");
	BoxComp->SetCollisionResponseToAllChannels(ECR_Overlap);
	BoxComp->SetBoxExtent(FVector::FVector(20.f));
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AENTProjectile::OnOverlap);

	PaperSpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>("Paper Sprite Component");
	PaperSpriteComp->SetupAttachment(BoxComp);

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

void AENTProjectile::SpawnSetup(ENTProjectileType SpawningClassType, float Dmg, float KnockBack)
{
	ProjectileType = SpawningClassType;
	if (ProjectileType == ENTProjectileType::PlayerProjectile)
	{
		PaperSpriteComp->SetSprite(PlayerProjectileSprite);
		KnockBackOutput = KnockBack;
	}
	else if (ProjectileType == ENTProjectileType::EnemyProjectile)
	{
		PaperSpriteComp->SetSprite(EnemyProjectileSprite);
	}
	DamageOutput = Dmg;
}

void AENTProjectile::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("%s"), *GetDebugName(OtherActor)));
	if (OtherActor->IsA(AENTEnemy::StaticClass()) && ProjectileType == ENTProjectileType::PlayerProjectile)
	{
		//UKismetSystemLibrary::PrintString(this, "Hit Enemy!");
		AENTEnemy* EnemyRef = Cast<AENTEnemy>(OtherActor);
		EnemyRef->ReceiveDamage(DamageOutput, KnockBackOutput);
		Destroy();
	}
	else if (OtherActor->IsA(AENTCharacter::StaticClass()) && ProjectileType == ENTProjectileType::EnemyProjectile)
	{
		AENTCharacter* CharRef = Cast<AENTCharacter>(OtherActor);
		CharRef->ReceiveDamage((uint32)DamageOutput);
		Destroy();
	}
}

