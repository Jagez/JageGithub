// Fill out your copyright notice in the Description page of Project Settings.


#include "GWeapon.h"
#include <Components/SkeletalMeshComponent.h>
#include "Kismet/GameplayStatics.h"

// Sets default values
AGWeapon::AGWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponComponent"));
	if (WeaponComponent != nullptr)
	{
		RootComponent	 = WeaponComponent;
		MuzzleSocketName = DEFAULT_MUZZLE_SOCKET_NAME;
		AmmoSocketName	 = DEFAULT_AMMO_SOCKET_NAME;
	}
	MuzzleLocation = FVector();
	MuzzleRotation = FRotator();
}

// Called when the game starts or when spawned
void AGWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	AActor* OwnerActor = GetOwner();
	if (nullptr != OwnerActor)
	{
		OwnerActor->GetActorEyesViewPoint(MuzzleLocation, MuzzleRotation);

	}
}

void AGWeapon::Fire()
{

}

void AGWeapon::StartFire()
{

}

void AGWeapon::StopFire()
{

}

void AGWeapon::PlayImpactEffect(EPhysicalSurface PhySurface, FVector ImpactPoint)
{
	switch (PhySurface)
	{
	case SURFACE_FLESHDEFAULT:
	case SURFACE_FLESHVULENRABLE:
		TargetImpactEffect = FleshImpactEffect;
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, TEXT("Flesh"));
		break;
	default:
		TargetImpactEffect = DefaultImpactEffect;
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, TEXT("Default"));
		break;
	}
	if (nullptr != TargetImpactEffect && nullptr != GetWorld())
	{
		FVector ShotLocation = ImpactPoint - MuzzleLocation;
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld()
			, TargetImpactEffect
			, ImpactPoint
			, ShotLocation.Rotation()
		);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, TEXT("Target is null"));
	}
}

void AGWeapon::PlayMuzzleEffect()
{
	if (nullptr != GetWorld())
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld()
			, MuzzleEffect
			, MuzzleLocation
		);
	}

}

// Called every frame
void AGWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

