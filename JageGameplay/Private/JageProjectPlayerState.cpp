// Fill out your copyright notice in the Description page of Project Settings.


#include "JageProjectPlayerState.h"
#include <string.h>


void AJageProjectPlayerState::AddSource(float Source)
{
	PlayerSource += Source;
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, FString::Printf(TEXT("%f"), Source));
}
