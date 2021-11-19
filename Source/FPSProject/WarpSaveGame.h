// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "WarpSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class FPSPROJECT_API UWarpSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UWarpSaveGame();

	UPROPERTY(VisibleAnywhere)
	FString levelName;

	UFUNCTION()
	void SetLevelName(FString newLevel);

	UPROPERTY(VisibleAnywhere)
	int isInit = 1;

	UPROPERTY(VisibleAnywhere)
	FVector playerPosition;

	UFUNCTION()
	void SetPlayerPosition(FVector newPosition);
	
};
