// Fill out your copyright notice in the Description page of Project Settings.

#include "ENTPlayerSelectWidget.h"
#include "ENTLocalPlayer.h"
#include "PaperSprite.h"
#include "Kismet/GameplayStatics.h"
#include "PaperSpriteBlueprintLibrary.h"
#include "SlateNoResource.h"

FSlateBrush UENTPlayerSelectWidget::GetPlayerOneImage() const
{
	return MakeBrushFromSprite(GetSpriteForPlayer(0), 150, 150);
}

FSlateBrush UENTPlayerSelectWidget::GetPlayerTwoImage() const
{
	return MakeBrushFromSprite(GetSpriteForPlayer(1), 150, 150);
}

FSlateBrush UENTPlayerSelectWidget::GetPlayerThreeImage() const
{
	return MakeBrushFromSprite(GetSpriteForPlayer(2), 150, 150);
}

FSlateBrush UENTPlayerSelectWidget::GetPlayerFourImage() const
{
	return MakeBrushFromSprite(GetSpriteForPlayer(3), 150, 150);
}

ENTCharacterClass UENTPlayerSelectWidget::GetCharacterClassForPlayer(int PlayerID) const
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, PlayerID);
	if (PC == nullptr) return ENTCharacterClass::NONE;

	if (UENTLocalPlayer* LocalPlayer = Cast<UENTLocalPlayer>(PC->GetLocalPlayer()))
	{
		return LocalPlayer->PlayerClass;
	}
	return ENTCharacterClass::NONE;
}

UPaperSprite* UENTPlayerSelectWidget::GetSpriteForPlayer(int PlayerID) const
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, PlayerID);
	if (PC == nullptr) return nullptr;

	if (UENTLocalPlayer* LocalPlayer = Cast<UENTLocalPlayer>(PC->GetLocalPlayer()))
	{
		if (DataTable && LocalPlayer->PlayerClass != ENTCharacterClass::NONE)
		{
			FName ClassName = EnumToFName("ENTCharacterClass", LocalPlayer->PlayerClass);
			FCharacterSpriteData* Row = DataTable->FindRow<FCharacterSpriteData>(ClassName, TEXT(""));

			if (LocalPlayer->PlayerColor == ENTColor::Blue)
				return Row->BlueSprite;
			else if (LocalPlayer->PlayerColor == ENTColor::Red)
				return Row->RedSprite;
			else if (LocalPlayer->PlayerColor == ENTColor::Green)
				return Row->GreenSprite;
			else
			return Row->PinkSprite;
		}
	}
	return nullptr;
}

FSlateBrush UENTPlayerSelectWidget::MakeBrushFromSprite(UPaperSprite* Sprite, int32 Width, int32 Height) const
{
	if (Sprite)
	{
		const FSlateAtlasData SpriteAtlasData = Sprite->GetSlateAtlasData();
		const FVector2D SpriteSize = SpriteAtlasData.GetSourceDimensions();

		FSlateBrush Brush;
		Brush.SetResourceObject(Sprite);
		Width = (Width > 0) ? Width : SpriteSize.X;
		Height = (Height > 0) ? Height : SpriteSize.Y;
		Brush.ImageSize = FVector2D(Width, Height);
		return Brush;
	}

	return FSlateNoResource();
}