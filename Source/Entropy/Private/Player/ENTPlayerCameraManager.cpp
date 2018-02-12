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
		FMinimalViewInfo OrigPOV = OutVT.POV;

		SharedCamera->GetCameraComponent()->GetCameraView(DeltaTime, OutVT.POV);

		OutVT.POV.PostProcessSettings.SetBaseValues();
		OutVT.POV.PostProcessBlendWeight = 1.0f;
	}
	else
	{
		Super::UpdateViewTarget(OutVT, DeltaTime);
	}
}
