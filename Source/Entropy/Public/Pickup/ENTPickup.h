// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ENTCharacterEnums.h"
#include "ENTPickup.generated.h"

UCLASS()
class ENTROPY_API AENTPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AENTPickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	FORCEINLINE ENTCharacterClass GetPickupClass() { return PickupClass; }

	void SetPickupClass(ENTCharacterClass ENTClass);
	void SetRandomPickupClass();

protected:

	void OnPickup(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(VisibleAnywhere)
	class UPaperSpriteComponent* SpriteComponent;
	
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxComponent;

	ENTCharacterClass PickupClass;

	UPROPERTY(EditAnywhere)
	UDataTable* DataTable;
	
private:

	void SetOrientation();

};
