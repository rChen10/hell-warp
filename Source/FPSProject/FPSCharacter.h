// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FPSProjectile.h"
#include "WarpSaveGame.h"
#include "MainGameInstance.h"
#include "FPSCharacter.generated.h"

UCLASS()
class FPSPROJECT_API AFPSCharacter : public ACharacter
{
GENERATED_BODY()

public:
// Sets default values for this character's properties
AFPSCharacter();

protected:
// Called when the game starts or when spawned
virtual void BeginPlay() override;

// Projectile class to spawn.
UPROPERTY(EditDefaultsOnly, Category = Projectile)
TSubclassOf<class AFPSProjectile> ProjectileClass;

public:
// Called every frame
virtual void Tick( float DeltaTime ) override;

// Called to bind functionality to input
virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

// Handles input for moving forward and backward.
UFUNCTION()
void MoveForward(float Value);

// Handles input for moving right and left.
UFUNCTION()
void MoveRight(float Value);

// Sets jump flag when key is pressed.
UFUNCTION()
void StartJump();

// Clears jump flag when key is released.
UFUNCTION()
void StopJump();

// Function that pushes to the warp stack.
UFUNCTION(BlueprintCallable, Category="Warp")
void PushWarp();

// Function that pops from the warp stack.
UFUNCTION(BlueprintCallable, Category="Warp")
void PopWarp();

// Function that warps after dying.
UFUNCTION(BlueprintCallable, Category="Warp")
bool DeathWarp();

// Function that pops from the warp stack.
UFUNCTION(BlueprintCallable, Category="Warp")
TArray<class UWarpSaveGame*> GetWarpStack();

// FPS camera
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
UCameraComponent* FPSCameraComponent;

// First-person mesh (arms), visible only to the owning player.
UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
USkeletalMeshComponent* FPSMesh;

// Gun muzzle offset from the camera location.
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
FVector MuzzleOffset;

// Warp Stack
TArray<class UWarpSaveGame*> WarpStack;

// Stats
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
float Health;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
float MaxHealth;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
float Damage;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
float Speed;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
int CurrentAmmo;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
int MaxAmmo;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
bool HasSMG;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
bool HasShotgun;
};