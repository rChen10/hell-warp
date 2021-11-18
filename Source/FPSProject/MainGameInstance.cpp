// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameInstance.h"

TArray<class UWarpSaveGame*> UMainGameInstance::GetWarpStack()
{
    return WarpStack;
}


void UMainGameInstance::PushWarpStack(FString nextLevel)
{
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

