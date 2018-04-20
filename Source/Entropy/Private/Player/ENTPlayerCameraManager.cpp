// Fill out your copyright notice in the Description page of Project Settings.

#include "ENTPlayerCameraManager.h"
#include "EntropyGameModeBase.h"
#include "ENTSharedCamera.h"
#include "Camera/CameraComponent.h"

void AENTPlayerCameraManager::BeginPlay()
{
	Super::BeginPlay();

	AEntropyGameModeBase* const GM = (GetWorld() != nullptr) ? GetWorld()->GetAuthGameMode<AEntropyGameModeBase>() : nullptr;

	if (GM)
	{
		SharedCamera = GM->GetSharedCamera();
	}
}

void AENTPlayerCameraManager::UpdateCamera(float DeltaTime)
{
	Super::UpdateCamera(DeltaTime);
}

void AENTPlayerCameraManager::UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime)
{
	if ((PendingViewTarget.Target != NULL) && BlendParams.bLockOutgoing && OutVT.Equal(ViewTarget))
	{
		return;
	}

	if (SharedCamera)
	{
		SharedCamera->GetCameraComponent()->GetCameraView(DeltaTime, OutVT.POV);
		OutVT.POV.PostProcessSettings = SharedCamera->GetCameraComponent()->PostProcessSettings;
		OutVT.POV.PostProcessBlendWeight = SharedCamera->GetCameraComponent()->PostProcessBlendWeight;
	}
	else
	{
		Super::UpdateViewTarget(OutVT, DeltaTime);
	}
}
