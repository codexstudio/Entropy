// Fill out your copyright notice in the Description page of Project Settings.

#include "ENTPlayerCameraManager.h"
#include "../../../../../../../UE4_UWP/Engine/Source/Runtime/Engine/Classes/Camera/CameraComponent.h"

void AENTPlayerCameraManager::BeginPlay()
{

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

		// 	OutVT.POV.FOV = SharedCamera->FieldOfView;
		// 	OutVT.POV.OrthoWidth = SharedCamera->OrthoWidth;
		// 	OutVT.POV.AspectRatio = SharedCamera->AspectRatio;
		// 	OutVT.POV.bConstrainAspectRatio = SharedCamera->bConstrainAspectRatio;
		// 	OutVT.POV.bUseFieldOfViewForLOD = SharedCamera->bUseFieldOfViewForLOD;
		// 	OutVT.POV.ProjectionMode = SharedCamera->ProjectionMode;

		SharedCamera->GetCameraView(DeltaTime, OutVT.POV);

		OutVT.POV.PostProcessSettings.SetBaseValues();
		OutVT.POV.PostProcessBlendWeight = 1.0f;
	}
	else
	{
		Super::UpdateViewTarget(OutVT, DeltaTime);
	}
}
