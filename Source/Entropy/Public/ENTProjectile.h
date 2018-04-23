// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperSprite.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ENTCharacterEnums.h"
#include "ENTProjectile.generated.h"

UCLASS()
class ENTROPY_API AENTProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AENTProjectile();

	UPROPERTY(VisibleAnywhere)
	class UPaperSpriteComponent* PaperSpriteComp;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxComp;

	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* ProjectileMovementComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE class AENTCharacter* GetENTOwner() { return ENTOwner; }

	void SpawnSetup(ENTProjectileType SpawningClassType, float Dmg, class AENTCharacter* ShootingActor = nullptr, float KnockBack = 0.0f);

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
protected:
	float DamageOutput;
	float KnockBackOutput = 0;

	class AENTCharacter* ENTOwner;
	ENTProjectileType ProjectileType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Sprites)
	UPaperSprite* PlayerProjectileSprite;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Sprites)
	UPaperSprite* EnemyProjectileSprite;
};
