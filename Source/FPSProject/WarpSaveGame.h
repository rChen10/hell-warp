// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "WarpSaveGame.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FPlayerStats
{
	GENERATED_BODY()

	UPROPERTY()
	float Health;

	UPROPERTY()
	float MaxHealth;

	UPROPERTY()
	float Damage;

	UPROPERTY()
	float Speed;

	UPROPERTY()
	int CurrentAmmo;

	UPROPERTY()
	int MaxAmmo;

	UPROPERTY()
	bool HasSMG;

	UPROPERTY()
	bool HasShotgun;
};

UCLASS()
class FPSPROJECT_API UWarpSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UWarpSaveGame();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString levelName;

	UFUNCTION()
	void SetLevelName(FString newLevel);

	UPROPERTY(VisibleAnywhere)
	int isInit = 1;

	UPROPERTY(VisibleAnywhere)
	FVector playerPosition;

	UFUNCTION()
	void SetPlayerPosition(FVector newPosition);
	

	UPROPERTY(VisibleAnywhere)
	FPlayerStats stats;

	UFUNCTION()
	void SetPlayerStats(FPlayerStats newStats);
};
