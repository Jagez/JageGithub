// Fill out your copyright notice in the Description page of Project Settings.


#include "GBaseActor.h"

// Sets default values
AGBaseActor::AGBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGBaseActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGBaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGBaseActor::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		if (NULL != ExplosionSound)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionSound, Hit.Location);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, Hit.Location);
		}
	}
	
}

