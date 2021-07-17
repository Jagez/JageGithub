// Fill out your copyright notice in the Description page of Project Settings.


#include "GExplosion.h"
#include "Components/StaticMeshComponent.h"
#include "GHealthComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Particles/ParticleSystem.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGExplosion::AGExplosion()
{
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	StaticMeshComp->SetSimulatePhysics(true);
	RootComponent = StaticMeshComp;

	//create RadialForceComponennt
	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComponent"));
	RadialForceComp->bImpulseVelChange	= true;
	RadialForceComp->bIgnoreOwningActor = false;
	RadialForceComp->Radius				= ExplosionRadius;
	RadialForceComp->SetupAttachment(RootComponent);

	//explosion effect
	ExplosionEffect = CreateDefaultSubobject<UParticleSystem>(TEXT("ExplosionEffect"));

	ExplosionRadius		= 250.f;
	ExplosionImpulse	= 400.f;

}

// Called when the game starts or when spawned
void AGExplosion::BeginPlay()
{
	Super::BeginPlay();
	
	if (nullptr != HealthComponent)
	{
		HealthComponent->OnHealthChanged.AddDynamic(this, &AGExplosion::OnHealthChanged);
	}
}

void AGExplosion::OnHealthChanged(class UGHealthComponent* HealthCoomponent
						, float Health
						, float DetlaHealth
						, const class UDamageType* DamageType
						, class AController* InstigatedBy
						, AActor* DamageCauser)
{
	if (Health == 0.f && nullptr != ExplosionEffect)
	{
		UWorld* GWorld = GetWorld();
		if (nullptr != GWorld)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GWorld
				, ExplosionEffect
				, GetActorLocation()
			);
			RadialForceComp->FireImpulse();
			StaticMeshComp->AddImpulse(ExplosionImpulse * FVector::UpVector		//UpVector -> (0, 0, 1)
				, NAME_None
				, true
				);
		}
	}
}

