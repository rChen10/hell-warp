// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameInstance.h"

void UMainGameInstance::Init()
{
    Super::Init();
    // Init with Black Level
	UWarpSaveGame* newWarp = NewObject<UWarpSaveGame>((UObject*) this, UWarpSaveGame::StaticClass());
	newWarp->SetLevelName(L"BlackMap");
    WarpStack.Add(newWarp);
}

TArray<class UWarpSaveGame*> UMainGameInstance::GetWarpStack()
{
    return WarpStack;
}


void UMainGameInstance::PushWarpStack(FString nextLevel, FVector playerPosition)
{
    // update the current warp
    if(WarpStack.Num() > 0)
    {
	    UWarpSaveGame* currentWarp = WarpStack[WarpStack.Num()-1];
	    currentWarp->SetPlayerPosition(playerPosition);
        currentWarp->isInit = 0;
    }
    // create the new warp
	UWarpSaveGame* newWarp = NewObject<UWarpSaveGame>((UObject*) this, UWarpSaveGame::StaticClass());
	newWarp->SetLevelName(nextLevel);
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

