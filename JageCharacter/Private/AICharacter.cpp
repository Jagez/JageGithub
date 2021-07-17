// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"
#include "NavigationSystem/Public/NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem/Public/NavigationPath.h"

// Sets default values
AAICharacter::AAICharacter()
{

}

FVector AAICharacter::GetNextNavPathPoint()
{
	ACharacter* PlayerPawn = UGameplayStatics::GetPlayerCharacter(this, 0);
	UNavigationPath* NavPath = UNavigationSystemV1::FindPathToActorSynchronously(this, GetActorLocation(), PlayerPawn);
	TArray<FVector> PathPoints = NavPath->PathPoints;
	if (PathPoints.Num() > 1)
	{
		return PathPoints[1];
	}
	else
	{
		return GetActorLocation();
	}
}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}
