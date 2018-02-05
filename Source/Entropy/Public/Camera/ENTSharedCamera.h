// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ENTSharedCamera.generated.h"

UCLASS()
class ENTROPY_API AENTSharedCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AENTSharedCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void CalcCameraPosition();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	TArray<AActor*> Players;

	UPROPERTY(EditAnywhere, Category = Camera)
	float CameraHeight;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* Camera;
};
