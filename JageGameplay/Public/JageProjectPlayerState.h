// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "JageProjectPlayerState.generated.h"


/**
 * 
 */
UCLASS()
class JAGEGAMEPLAY_API AJageProjectPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "PlayerState")
	void AddSource(float Source);

protected:
	float PlayerSource;
};
