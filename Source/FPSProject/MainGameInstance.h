// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "WarpSaveGame.h"
#include "MainGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FPSPROJECT_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	void Init() override;

	// Get the Warp Stack
	UFUNCTION(BlueprintCallable, Category="Update State")
	TArray<class UWarpSaveGame*> GetWarpStack();

	// Push to the Warp Stack
	UFUNCTION(BlueprintCallable, Category="Update State")
	void PushWarpStack(FString nextLevel, FVector playerPosition);
	
	// Pop the Warp Stack
	UFUNCTION(BlueprintCallable, Category="Update State")
	UWarpSaveGame* PopWarpStack();

	// Warp Stack
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Warp")
	TArray<class UWarpSaveGame*> WarpStack;
};
