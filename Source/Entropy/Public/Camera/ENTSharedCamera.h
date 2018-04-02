// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ENTSharedCamera.generated.h"

class UCameraComponent;

UCLASS()
class ENTROPY_API AENTSharedCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AENTSharedCamera();

	FORCEINLINE UCameraComponent* GetCameraComponent() { return CameraComp; }
	FORCEINLINE TArray<AActor*> GetPlayers() const { return Players; }

	float GetOrthoWidth() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector CalcCameraPosition();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	TArray<AActor*> Players;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* CameraBoomComp;
};
