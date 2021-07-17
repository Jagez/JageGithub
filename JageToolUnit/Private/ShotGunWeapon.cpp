// Fill out your copyright notice in the Description page of Project Settings.


#include "ShotGunWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Particles/ParticleSystem.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include <Particles/ParticleSystemComponent.h>

// Sets default values
AShotGunWeapon::AShotGunWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ShotGunComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ShotGunComponennt"));
	RootComponent = ShotGunComponent;

	MuzzleSocketName = "MuzzleSocket";

}

// Called when the game starts or when spawned
void AShotGunWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AShotGunWeapon::Fire()
{
	AActor* OwnerActor = GetOwner();
	if (nullptr != OwnerActor)
	{
		FVector EyesLocation;
		FRotator EyesRotation;
		//APawn* OwnerPawn = Cast<APawn>(Owner);
		//if (OwnerPawn != nullptr)
		{
			//for a pawn, this would define a eyes height location,we need Camera Location
			OwnerActor->GetActorEyesViewPoint(EyesLocation, EyesRotation);	//RootComponent's Height Location
			FHitResult Hit;
			FVector TraceEnd = EyesLocation + (EyesRotation.Vector() * 1000);
			FCollisionQueryParams QueryParams;
			QueryParams.AddIgnoredActor(OwnerActor);		//ignored weapon
			QueryParams.AddIgnoredActor(this);		//ignored player
			QueryParams.bTraceComplex = true;		//more accuration 
			bool TraceRes = GetWorld()->LineTraceSingleByChannel(Hit, EyesLocation, TraceEnd, ECC_Visibility, QueryParams);
			if (TraceRes)
			{
				DrawDebugLine(GetWorld(), EyesLocation, TraceEnd, FColor::Red, false, 2.f, 0, 1.f);
				AActor* HitActor = Hit.GetActor();
				UGameplayStatics::ApplyPointDamage(HitActor, 20.f
					, TraceEnd
					, Hit
					, OwnerActor->GetInstigatorController()
					, this
					, DamageType);
				if (nullptr != ImpactEffect)
				{
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect
						, Hit.ImpactPoint
						, Hit.ImpactNormal.Rotation()
					);
				}
				
			}
			if (nullptr != ImpactEffect && nullptr != TracerEffect)
			{
				FVector MuzzleLocation = ShotGunComponent->GetSocketLocation(MuzzleSocketName);
				UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, ShotGunComponent, MuzzleSocketName);
				UParticleSystemComponent* TracerComponent =  UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TracerEffect, MuzzleLocation);
				if (nullptr != TracerComponent)
				{
					//TracerComponent->SetVectorParameter()
				}
			}

		}
	}
}

// Called every frame
void AShotGunWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

