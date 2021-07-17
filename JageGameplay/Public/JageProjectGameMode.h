// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "JageProjectGameMode.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnActorKilledSignature, AActor*, Victim, AActor*, Killer, AController*, KillerController);


UCLASS()
class JAGEGAMEPLAY_API AJageProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AJageProjectGameMode();

	void StartPlay() override;

	UFUNCTION()
	void Completed();

	virtual int32 GetNumPlayers() override;

	void Tick(float DeltaSeconds) override;

	void RestartPlayers();

	void RunLevel();

public:

	UPROPERTY(BlueprintAssignable, Category = "GameMode")
	FOnActorKilledSignature OnActorKilled;

protected:
	uint8_t Waves;

	uint8_t NumOfSpawns;
	//关卡切换需要的时间
	float TimeBetweenWave;

	FTimerHandle TurnWaveTimerHandle;

	FTimerHandle SpawnerTimerHandle;

	UPROPERTY(BlueprintReadOnly, Category = "GameMode")
	bool IsSomeoneAlive;

protected:

	UFUNCTION()
	void StartWave();

	UFUNCTION()
	void EndWave();

	UFUNCTION()
	void NextWave();

	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
	void SpawnBot();

	UFUNCTION()
	void TimeToSpawn();

	UFUNCTION()
	void CheckState();

};



