// Fill out your copyright notice in the Description page of Project Settings.

#include "ENTPlayerSelectWidget.h"
#include "ENTLocalPlayer.h"
#include "ENTCharacterEnums.h"

FSlateBrush UENTPlayerSelectWidget::GetPlayerOneImage() const
{
	FSlateBrush Ret;
	if (UENTLocalPlayer* LocalPlayer = Cast<UENTLocalPlayer>(GetOwningLocalPlayer()))
	{
		if (DataTable)
		{
			FCharacterSpriteData* Row = DataTable->FindRow(LocalPlayer->PlayerClass
			switch (LocalPlayer->PlayerColor)
			{
			case FColor::Blue:
			}
		}
	}
	return FSlateBrush();
}

FSlateBrush UENTPlayerSelectWidget::GetPlayerTwoImage() const
{
	return FSlateBrush();
}

FSlateBrush UENTPlayerSelectWidget::GetPlayerThreeImage() const
{
	return FSlateBrush();
}

FSlateBrush UENTPlayerSelectWidget::GetPlayerFourImage() const
{
	return FSlateBrush();
}

