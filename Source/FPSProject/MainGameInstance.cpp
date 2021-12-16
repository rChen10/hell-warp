// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameInstance.h"

void UMainGameInstance::Init()
{
    Super::Init();
    // Init with Black Level
	UWarpSaveGame* newWarp = NewObject<UWarpSaveGame>((UObject*) this, UWarpSaveGame::StaticClass());
	newWarp->SetLevelName(L"BlackMap");

	FPlayerStats statsStore;
	statsStore.Health = 100; statsStore.MaxHealth = 100;	
	statsStore.Damage = 1; statsStore.Speed = 1;
	statsStore.CurrentAmmo = 200; statsStore.MaxAmmo = 200;
    newWarp->stats = statsStore;

    WarpStack.Add(newWarp);
}

TArray<class UWarpSaveGame*> UMainGameInstance::GetWarpStack()
{
    return WarpStack;
}


void UMainGameInstance::PushWarpStack(FString nextLevel, FVector playerPosition, FPlayerStats playerStats)
{
    // update the current warp
    if(WarpStack.Num() > 0)
    {
	    UWarpSaveGame* currentWarp = WarpStack[WarpStack.Num()-1];
	    currentWarp->SetPlayerPosition(playerPosition);
	    currentWarp->SetPlayerStats(playerStats);
        currentWarp->isInit = 0;
    }
    // create the new warp
	UWarpSaveGame* newWarp = NewObject<UWarpSaveGame>((UObject*) this, UWarpSaveGame::StaticClass());
	newWarp->SetLevelName(nextLevel);
	newWarp->SetPlayerStats(playerStats);
    WarpStack.Add(newWarp);
}

UWarpSaveGame* UMainGameInstance::PopWarpStack()
{
    if (WarpStack.Num() > 0)
    {
        UWarpSaveGame* top = WarpStack[WarpStack.Num()-1];
        WarpStack.RemoveAt(WarpStack.Num() - 1);
        return top;
    }
    else
    {
        return nullptr;
    }
}

void UMainGameInstance::StatsWarpStack(FPlayerStats newStats)
{
    if (WarpStack.Num() > 0)
    {
	    UWarpSaveGame* currentWarp = WarpStack[WarpStack.Num()-1];
	    currentWarp->SetPlayerStats(newStats);
    }
}

