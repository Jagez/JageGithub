// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "GBaseActor.generated.h"

UCLASS()
class JAGEPROJECT_API AGBaseActor : public AActor
{
	GENERATED_BODY()

	

public:	
	// Sets default values for this actor's properties
	AGBaseActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			FVector NormalImpulse,
			const FHitResult& Hit);

public:

	UPROPERTY(EditDefaultsOnly, Category = "GBase")
	USoundBase * ExplosionSound;

	UPROPERTY(EditDefaultsOnly, Category = "GBase")
	UParticleSystem * ExplosionEffect;

protected:

	//Group
	struct _CharactorGroup
	{
		//group ID
		UINT16 CharactorGroupID;
	};
};
