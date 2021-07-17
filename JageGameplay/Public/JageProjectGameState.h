// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "JageProjectGameState.generated.h"

UENUM(BlueprintType)
enum class EWaveState : uint8
{
	WaitingStart,
	WaveProgressing,
	WaitToCompleted,
	WaveCompleted,
	GameOver
};

/**
 * 
 */
UCLASS()
class JAGEGAMEPLAY_API AJageProjectGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UFUNCTION(NetMulticast, Reliable)
	void MulticastTest(APawn* InstigatorPawn, bool b);

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, Category = "GameState")
	void SetWaveState(EWaveState NewState, EWaveState OldState);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
		TSubclassOf<UDamageType> DamageType;
protected:
	UFUNCTION()
	void OnRep_WaveState(EWaveState OldState);

	UFUNCTION(BlueprintImplementableEvent, Category = "GameState")
	void OnWaveStateChanged(EWaveState NewState, EWaveState OldState);
protected:
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = "OnRep_WaveState", Category = "GameState")
	EWaveState WaveState;
	
	
};
