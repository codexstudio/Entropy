// Fill out your copyright notice in the Description page of Project Settings.

#include "EntropyGameModeBase.h"
#include "Entropy.h"
#include "ENTSharedCamera.h"

void AEntropyGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void AEntropyGameModeBase::SetSharedCamera(AENTSharedCamera* InSharedCamera)
{
	SharedCamera = InSharedCamera;
}