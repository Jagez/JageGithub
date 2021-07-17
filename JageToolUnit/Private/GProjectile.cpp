// Fill out your copyright notice in the Description page of Project Settings.


#include "GProjectile.h"
#include "GToolCommon.h"
#include <Components/SkeletalMeshComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <Components/SphereComponent.h>
#include <Kismet/GameplayStatics.h>

// Sets default values
AGProjectile::AGProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InitProjectileSpeed = 100.f;;
	MaxProjectileSpeed = 6000.f;
	bVelocitySpeed = true;
	bProjectileBounce = false;

	InitialLifeSpan = 2.f;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	if (nullptr != CollisionComponent) 
	{
		CollisionComponent->BodyInstance.SetCollisionProfileName("Projectile");
		CollisionComponent->bReturnMaterialOnMove = true;
		CollisionComponent->SetCollisionObjectType(COLLISION_CHANNEL);
		//CollisionComponent->OnComponentHit.AddDynamic(this, &AGProjectile::OnHit);
		RootComponent = CollisionComponent;
	}

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComponent"));
	if (nullptr != ProjectileMovement && nullptr != CollisionComponent)
	{
		ProjectileMovement->UpdatedComponent = CollisionComponent;
		ProjectileMovement->MaxSpeed = MaxProjectileSpeed;
		ProjectileMovement->InitialSpeed = InitProjectileSpeed;
		ProjectileMovement->bRotationFollowsVelocity = bVelocitySpeed;
		ProjectileMovement->bShouldBounce = bProjectileBounce;
	}

	//replicated to network.
	//SetReplicates(true);
	//SetReplicateMovement(true);
}

void AGProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Destroy();
}

// Called when the game starts or when spawned
void AGProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGProjectile::SetProjectileMaxSpeed(float MaxSpeed)
{
	MaxProjectileSpeed = MaxSpeed;
}

void AGProjectile::SetProjectileInitSpeed(float InitSpeed)
{
	InitProjectileSpeed = InitSpeed;
}

void AGProjectile::SetVelocitySpeed(bool bVelocity)
{
	bVelocitySpeed = bVelocity;
}

void AGProjectile::SetBounce(bool bBounce)
{
	bProjectileBounce = bBounce;
}

void AGProjectile::SetDamage(float Value)
{
	Damage = Value;
}

// Called every frame
void AGProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

