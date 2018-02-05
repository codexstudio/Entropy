// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EntropyGameModeBase.generated.h"

class AENTSharedCamera;

UCLASS()
class ENTROPY_API AEntropyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	FORCEINLINE AENTSharedCamera* GetSharedCamera() { return SharedCamera; }

	// called from level blueprint to set shared camera to persistent camera actor 
	// that is already placed in the world
	UFUNCTION(BlueprintCallable, Category = Camera)
	void SetSharedCamera(AENTSharedCamera* InSharedCamera);

protected:
	virtual void BeginPlay() override;

protected:
	// you would want this in game state or game instance if this was a networked game
	AENTSharedCamera* SharedCamera;

};