// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a first person camera component.
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	check(FPSCameraComponent != nullptr);
	
	// Attach the camera component to our capsule component.
	FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));

	// Position the camera slightly above the eyes.
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
	
	// Enable the pawn to control camera rotation.
	FPSCameraComponent->bUsePawnControlRotation = true;

	// Create a first person mesh component for the owning player.
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	check(FPSMesh != nullptr);
	
	// Only the owning player sees this mesh.
	FPSMesh->SetOnlyOwnerSee(true);
	
	// Attach the FPS mesh to the FPS camera.
	FPSMesh->SetupAttachment(FPSCameraComponent);
	
	// Disable some environmental shadows to preserve the illusion of having a single mesh.
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;

	// The owning player doesn't see the regular (third-person) body mesh.
	GetMesh()->SetOwnerNoSee(true);

	// Default Stats
	Health = 100;
	MaxHealth = 100;
	Damage = 1;
	Speed = 1;
	CurrentAmmo = 100;
	MaxAmmo = 200;
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	check(GEngine != nullptr);

	// Display a debug message for five seconds. 
	// The -1 "Key" value argument prevents the message from being updated or refreshed.
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FPSCharacter."));

	// Retrieve the Warp Stack from the Game Instance
	UMainGameInstance *gameInstance = Cast<UMainGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (gameInstance) {
		WarpStack = gameInstance->GetWarpStack();
		if (WarpStack.Num() > 0)
		{
			UWarpSaveGame* top = WarpStack[WarpStack.Num() - 1];
			if (top->isInit == 0)
			{
				SetActorLocation(top->playerPosition);
			}
			FPlayerStats playerStats = top->stats;
			Health = playerStats.Health; MaxHealth = playerStats.MaxHealth;
			Damage = playerStats.Damage; Speed = playerStats.Speed;
			CurrentAmmo = playerStats.CurrentAmmo; MaxAmmo = playerStats.MaxAmmo;
			HasSMG = playerStats.HasSMG; HasShotgun = playerStats.HasShotgun;
		}
	}
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up "movement" bindings.
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);

	// Set up "look" bindings.
	PlayerInputComponent->BindAxis("Turn", this, &AFPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AFPSCharacter::AddControllerPitchInput);

	// Set up "action" bindings.
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::StopJump);
}

void AFPSCharacter::MoveForward(float Value)
{
    // Find out which way is "forward" and record that the player wants to move that way.
    FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
    AddMovementInput(Direction, Value);
}

void AFPSCharacter::MoveRight(float Value)
{
    // Find out which way is "right" and record that the player wants to move that way.
    FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
    AddMovementInput(Direction, Value);
}

void AFPSCharacter::StartJump()
{
    bPressedJump = true;
}

void AFPSCharacter::StopJump()
{
    bPressedJump = false;
}

void AFPSCharacter::PushWarp()
{
	TArray<FString> levelNames = TArray<FString>();
	FString Arr[] = { L"RedMap", L"BlueMap", L"GreenMap" };
	for (int i = 0; i < 3; i++)
	{
		FString level = Arr[i];
		int isPresent = 0;
		for (int j = 0; j < WarpStack.Num(); j++)
		{
			FString warpLevel = WarpStack[j]->levelName;
			if (warpLevel.Equals(level))
			{
				isPresent = 1;
				break;
			}
		}
		if (isPresent == 0)
		{
			levelNames.Add(level);
		}
	}
	if (levelNames.Num() == 0)
	{
		return;
	}
	int iRandomLevel = FMath::RandRange(0, levelNames.Num()-1);
	FName nextLevelName = FName(*levelNames[iRandomLevel]);
	FVector position = GetActorLocation();
	UMainGameInstance *gameInstance = Cast<UMainGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	// Create Stats Storage
	FPlayerStats statsStore;
	statsStore.Health = Health; statsStore.MaxHealth = MaxHealth;	
	statsStore.Damage = Damage; statsStore.Speed = Speed;
	statsStore.CurrentAmmo = CurrentAmmo; statsStore.MaxAmmo = MaxAmmo;
    statsStore.HasSMG = HasSMG; statsStore.HasShotgun = HasShotgun;

	gameInstance->PushWarpStack(levelNames[iRandomLevel], position, statsStore);
	WarpStack = gameInstance->GetWarpStack();
	UGameplayStatics::OpenLevel(GetWorld(), nextLevelName);
}

void AFPSCharacter::PopWarp()
{
	if (WarpStack.Num() <= 1)
	{
		return;
	}
	UMainGameInstance *gameInstance = Cast<UMainGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	gameInstance->PopWarpStack();

	// Create Stats Storage
	FPlayerStats statsStore;
	statsStore.Health = Health; statsStore.MaxHealth = MaxHealth;	
	statsStore.Damage = Damage; statsStore.Speed = Speed;
	statsStore.CurrentAmmo = CurrentAmmo; statsStore.MaxAmmo = MaxAmmo;
    statsStore.HasSMG = HasSMG; statsStore.HasShotgun = HasShotgun;

	gameInstance->StatsWarpStack(statsStore);

	WarpStack = gameInstance->GetWarpStack();
	UWarpSaveGame* nextLevel = WarpStack[WarpStack.Num() - 1];
	FName nextLevelName = FName(*nextLevel->levelName);
	UGameplayStatics::OpenLevel(GetWorld(), nextLevelName);
}

bool AFPSCharacter::DeathWarp()
{
	if (WarpStack.Num() <= 1)
	{
		// You Lose
		return true;
	}
	UMainGameInstance *gameInstance = Cast<UMainGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	gameInstance->PopWarpStack();

	WarpStack = gameInstance->GetWarpStack();
	UWarpSaveGame* nextLevel = WarpStack[WarpStack.Num() - 1];
	FName nextLevelName = FName(*nextLevel->levelName);
	UGameplayStatics::OpenLevel(GetWorld(), nextLevelName);
	return false;
}

TArray<class UWarpSaveGame*> AFPSCharacter::GetWarpStack()
{
	return WarpStack;
}

