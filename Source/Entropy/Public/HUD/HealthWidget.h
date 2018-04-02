// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthWidget.generated.h"

/**
 * 
 */
UCLASS()
class ENTROPY_API UHealthWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	class UImage* GetImage();

protected:
	UPROPERTY(meta = (BindWidget))
	class UImage* BarImage;
};
