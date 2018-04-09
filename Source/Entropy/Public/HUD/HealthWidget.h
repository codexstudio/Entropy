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
	void RepresentHealth(uint32 Health);
	void InitWidget();

protected:
	
	UFUNCTION(BlueprintImplementableEvent)
	class UMaterialInstance* GetMatInstance() const;

	UPROPERTY(meta = (BindWidget))
	class UImage* BarImage;
		
	class UMaterialInstanceDynamic* MatInstance;

	
};
