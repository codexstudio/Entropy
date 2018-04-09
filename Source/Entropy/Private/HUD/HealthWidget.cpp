// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthWidget.h"
#include "Image.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Materials/MaterialInstanceDynamic.h"


void UHealthWidget::RepresentHealth(uint32 Health)
{
	if (MatInstance)
	{
		int StepCount = (Health + 4 - 1) / 4 * 4;
		BarImage->GetDynamicMaterial()->SetScalarParameterValue("StepCount", StepCount);
		BarImage->GetDynamicMaterial()->SetScalarParameterValue("Percent", ((float)Health / (float)StepCount));
	}
}

void UHealthWidget::InitWidget()
{
	MatInstance = UMaterialInstanceDynamic::Create(GetMatInstance(), this);
	BarImage->SetBrushFromMaterial(MatInstance);
}
