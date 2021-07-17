// Fill out your copyright notice in the Description page of Project Settings.


#include "JageProjectGameState.h"
#include "JageProjectPlayerController.h"
#include "Engine/World.h"
#include "UnrealNetwork.h"

void AJageProjectGameState::MulticastTest_Implementation(APawn* InstigatorPawn, bool b)
{
	const uint32 TimeMin = GetServerWorldTimeSeconds() / 60;
	const uint32 TimeSec = (uint32)(GetServerWorldTimeSeconds()) % 60;
	GEngine->AddOnScreenDebugMessage(-1, 13.f, FColor::Red
		, FString::Printf(TEXT("WorldTime: %02d:%02d"), TimeMin, TimeSec)
	);
	for (APlayerState* state : PlayerArray)
	{

	}
	GEngine->AddOnScreenDebugMessage(-1, 13.f, FColor::Red
		, FString::Printf(TEXT("Is start game: %s"), HasBegunPlay() ? "Yes" : "No")
	);
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator() ; It; ++It )
	{
		AJageProjectgePlayerController* PlayerController = Cast<AJageProjectgePlayerController>(It->Get());
		if (nullptr != PlayerController && PlayerController->IsLocalPlayerController())
		{
			//PlayerController->OnCompleted();
			APawn * Pawn = PlayerController->GetPawn();
			if (nullptr != Pawn)
			{
				GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Completed."));
				//Pawn->DisableInput(nullptr); //ok
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("PlayerController is null."));
		}
	}
	
	
	
}

void AJageProjectGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AJageProjectGameState, WaveState);
}

void AJageProjectGameState::SetWaveState(EWaveState NewState, EWaveState OldState)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		WaveState = NewState;
		OnRep_WaveState(OldState);
	}
}

void AJageProjectGameState::OnRep_WaveState(EWaveState OldState)
{
	OnWaveStateChanged(WaveState, OldState);
}
