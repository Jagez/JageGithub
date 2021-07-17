// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "JageProjectGameMode.h"
//#include "JageProjectHUD.h"
//#include "JageProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "JageProjectGameState.h"
#include "JageProjectPlayerController.h"
#include "JageProjectPlayerState.h"
#include <stdexcept>
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
//#include "Components/GHealthComponent.h"

AJageProjectGameMode::AJageProjectGameMode()
	: Super()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 1.f;
	TimeBetweenWave = 2.f;
	IsSomeoneAlive = true;

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	//HUDClass = AJageProjectHUD::StaticClass();

	// set Default GameState
	GameStateClass			= AJageProjectGameState::StaticClass();
	PlayerStateClass		= AJageProjectPlayerState::StaticClass();
	PlayerControllerClass	= AJageProjectgePlayerController::StaticClass();
	

}

void AJageProjectGameMode::StartPlay()
{
	Super::StartPlay();
	StartWave();
}


void AJageProjectGameMode::Completed()
{
	AJageProjectGameState* GS = GetGameState<AJageProjectGameState>();
	if (nullptr != GS)
	{
		GS->MulticastTest(nullptr, true);
	}
	//UGameplayStatics::OpenLevel(GetWorld(), TEXT(""), true);
	GEngine->AddOnScreenDebugMessage(-1, 13.f, FColor::Red, FString::Printf(TEXT("Players: %d"), GetNumPlayers()));
}

int32 AJageProjectGameMode::GetNumPlayers()
{
	return Super::GetNumPlayers();
}

void AJageProjectGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	CheckState();
}

void AJageProjectGameMode::RestartPlayers()
{
	//循环遍历playercontroller，再判断其pawn是不是空（已销毁）,然后重新产生Player
	FConstPlayerControllerIterator PlayerControllers = GetWorld()->GetPlayerControllerIterator();
	for (FConstPlayerControllerIterator It = PlayerControllers; It->IsValid(); It++)
	{
		APlayerController* TempController = It->Get();
		if (nullptr != TempController && nullptr == TempController->GetPawn())
		{
			RestartPlayer(TempController);
		}
	}
}

void AJageProjectGameMode::StartWave()
{
	Waves++;
	NumOfSpawns = 3 * Waves;
	GetWorldTimerManager().SetTimer(SpawnerTimerHandle, this, &AJageProjectGameMode::TimeToSpawn, 1.f, true, 0);
}

void AJageProjectGameMode::EndWave()
{
	GetWorldTimerManager().ClearTimer(SpawnerTimerHandle);
	NextWave();
}

void AJageProjectGameMode::NextWave()
{
	FTimerHandle NextWaveTimerHandle;
	GetWorldTimerManager().SetTimer(NextWaveTimerHandle,this, &AJageProjectGameMode::StartWave, TimeBetweenWave, false);

	//RestartPlayers();
}

void AJageProjectGameMode::TimeToSpawn()
{
	SpawnBot();
	NumOfSpawns--;
	if (NumOfSpawns <= 0)
	{
		EndWave();
	}
}

void AJageProjectGameMode::CheckState()
{
	for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
	{
		APawn* TempPawn = It->Get();
		if (TempPawn != nullptr && TempPawn->IsPlayerControlled())
		{
			continue;
		}

		if (true == IsSomeoneAlive)
		{

		}
	}
}

