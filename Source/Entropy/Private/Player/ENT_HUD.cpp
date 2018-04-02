// Fill out your copyright notice in the Description page of Project Settings.

#include "ENT_HUD.h"
#include "UserWidget.h"

void AENT_HUD::BeginPlay()
{
	Super::BeginPlay();

	//ChangeMenuWidget(StartingWidgetClass);


}

void AENT_HUD::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetOwningPlayerController(), NewWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

