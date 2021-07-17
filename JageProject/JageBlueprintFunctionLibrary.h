// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "JageBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class JAGEPROJECT_API UJageBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = LoadingScreenBPLib)
	static void StartPlayingLoadingScreen(bool bLoadingAbt, float durTime);
	
	UFUNCTION(BlueprintCallable, Category = LoadingScreenBPLib)
	static void StopPlayingLoadingScreen();

	//UFUNCTION(BlueprintCallable, Category = MetarialsBPLib)
	//static float sdTriangle(float a, float b, in float2 c);
};
