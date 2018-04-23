// Fill out your copyright notice in the Description page of Project Settings.

#include "ENTLocalPlayer.h"

void UENTLocalPlayer::PlayerAdded(class UGameViewportClient* InViewportClient, int32 InControllerID)
{
	Super::PlayerAdded(InViewportClient, InControllerID);

	PlayerClass = ENTCharacterClass::NONE;
	PlayerColor = ENTColor::Blue;
}
