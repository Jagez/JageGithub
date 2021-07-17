// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonCameraActor.h"

// Sets default values
AThirdPersonCameraActor::AThirdPersonCameraActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ThirdCameraActor = CreateDefaultSubobject<AActor>(TEXT("ThirdPersonCamera"));
	
}

// Called when the game starts or when spawned
void AThirdPersonCameraActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AThirdPersonCameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

