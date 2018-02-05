// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "ENTPlayerCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class ENTROPY_API AENTPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
	
public:
	virtual void UpdateCamera(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime) override;

protected:
	class AENTSharedCamera* SharedCamera;
};
