// Fill out your copyright notice in the Description page of Project Settings.


#include "WarpSaveGame.h"

UWarpSaveGame::UWarpSaveGame()
{
}

void UWarpSaveGame::SetLevelName(FString newLevel)
{
    levelName = newLevel;
}

void UWarpSaveGame::SetPlayerPosition(FVector newPosition)
{
    playerPosition = newPosition;
}

void UWarpSaveGame::SetPlayerStats(FPlayerStats newStats)
{
    stats = newStats;
}

