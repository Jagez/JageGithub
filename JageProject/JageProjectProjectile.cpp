// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "JageProjectProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "JageProjectCharacter.h"

AJageProjectProjectile::AJageProjectProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AJageProjectProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;

	//allow call Tick() event
	PrimaryActorTick.bCanEverTick = true;
	// client replicate, only replicate on client
	SetReplicates(true);
	SetReplicateMovement(true);

}

void AJageProjectProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UGameplayStatics::ApplyDamage(OtherActor, 10.f, OtherActor->GetInstigatorController(), this, TSubclassOf<UDamageType>(UDamageType::StaticClass()));
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		//client will return null, server will return current gameMode.
		GetWorld()->GetAuthGameMode();

	}
	//'Role' 已经被相应替换为 'GetLocalRole()' 和 'GetRemoteRole()'
	if (GetLocalRole() == ROLE_Authority)
	{

		MakeNoise(1.f, GetInstigator());		//4.22以前使用Instigator
		//销毁当前projectile
		Destroy();
	}
	
	

}

void AJageProjectProjectile::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
