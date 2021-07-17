// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AICharacter.generated.h"

UCLASS()
class JAGECHARACTER_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAICharacter();

	FVector GetNextNavPathPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:

	UPROPERTY()
	FVector NavPathNextPoint;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float DistanceOfTarget;

public:	

};
