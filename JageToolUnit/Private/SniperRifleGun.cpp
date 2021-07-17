// Fill out your copyright notice in the Description page of Project Settings.


#include "SniperRifleGun.h"
#include "Components/SphereComponent.h"
#include <Kismet/GameplayStatics.h>
#include "SniperRifleProjectile.h"
#include <Engine/World.h>
#include <UnrealNetwork.h>
#include "Camera/CameraShakeBase.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "TimerManager.h"
#include "GToolCommon.h"

ASniperRifleGun::ASniperRifleGun()
{
	ProjectileDamage = DEFAULT_SNIPERRIFLE_PROJECTILE_DAMAGE;
	ShotOfRate = 100;
	BulletSpread = 2.f;

	//NetUpdateFrequency = 60.f;
	//MinNetUpdateFrequency = 30.f;

	SetReplicates(true);
}

void ASniperRifleGun::Fire()
{
	
	if (nullptr != FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSound, GetActorLocation());
	}

	if (nullptr != WeaponComponent && nullptr != MuzzleEffect)
	{
		MuzzleLocation = WeaponComponent->GetSocketLocation(MuzzleSocketName);
		FVector ShotDirection = FVector::ZeroVector;
		PlayMuzzleEffect();

		//World spawns projectile actor.
		UWorld* TempWorld = GetWorld();
		if (nullptr != TempWorld && ProjectileClass != nullptr)
		{
			APawn* PawnOwner = Cast<APawn>(GetOwner());
			APlayerController* PlayerContr = nullptr;
			if (nullptr != PawnOwner)
			{
				MuzzleRotation = PawnOwner->GetControlRotation();

				//TODO 枪口振幅
				float HalfRad = FMath::DegreesToRadians(BulletSpread);
				ShotDirection = FMath::VRandCone(MuzzleRotation.Vector(), HalfRad, HalfRad); 

				PlayerContr = Cast<APlayerController>(PawnOwner->GetController());
			}
			FActorSpawnParameters SpawnParameters;
			//Actor 将尝试找到附近的非碰撞位置（基于形状组件），但除非找到，否则不会生成。
			SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			SpawnParameters.Instigator = nullptr;
			ASniperRifleProjectile* Projectile = TempWorld->SpawnActor<ASniperRifleProjectile>(ProjectileClass
				, MuzzleLocation
				, MuzzleRotation
				, SpawnParameters);

			if (nullptr != Projectile)
			{
				FHitResult Hit;
				FVector TraceStart = MuzzleLocation;
				FVector TraceEnd = (MuzzleRotation.Vector() * 1000) + MuzzleLocation;
				FCollisionQueryParams QueryParams;
				QueryParams.AddIgnoredActor(GetOwner());
				QueryParams.AddIgnoredActor(this);
				QueryParams.bTraceComplex = true;
				QueryParams.bReturnPhysicalMaterial = true;

				EPhysicalSurface PhySurfaceType = EPhysicalSurface::SurfaceType_Default;
				Projectile->SetDamage(ProjectileDamage);
				Projectile->CollisionComponent->OnComponentHit.AddDynamic(this, &ASniperRifleGun::OnHit);
				bool bTraceRes = TempWorld->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, COLLISION_CHANNEL, QueryParams);
				if (true == bTraceRes)
				{
					float damage = UGameplayStatics::ApplyPointDamage(Hit.GetActor()
						, ProjectileDamage
						, TraceEnd
						, Hit
						, GetOwner()->GetInstigatorController()
						, this
						, DamageType);
					PhySurfaceType = UPhysicalMaterial::DetermineSurfaceType(Hit.PhysMaterial.Get());
					PlayImpactEffect(PhySurfaceType, Hit.ImpactPoint);

					//replicate struct FHitScanTrace
					if (GetLocalRole() == ROLE_Authority)
					{
						HitScanTrace.BurstCounter++;
						HitScanTrace.TraceTo = TraceEnd;
						HitScanTrace.SurfaceType = PhySurfaceType;
					}
				}
			}
			if (nullptr != PlayerContr)
			{
				PlayerContr->ClientStartCameraShake(CameraShakeClass);
			}
		}
	}
	

	LastTimeFire = GetWorld()->TimeSeconds;
}

void ASniperRifleGun::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	/*if (nullptr != TargetImpactEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld()
			, TargetImpactEffect
			, Hit.ImpactPoint
			, Hit.ImpactNormal.Rotation()
		);
	}*/

	EPhysicalSurface PhySurfaceType = UPhysicalMaterial::DetermineSurfaceType(Hit.PhysMaterial.Get());
	
	//PlayImpactEffect(HitScanTrace.SurfaceType, Hit.ImpactPoint);
	PlayImpactEffect(PhySurfaceType, Hit.ImpactPoint);
}

void ASniperRifleGun::OnRep_ProjectileDamage()
{

}

void ASniperRifleGun::OnRep_HitScanTrace()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("HitScan"));
	PlayImpactEffect(HitScanTrace.SurfaceType, HitScanTrace.TraceTo);
	PlayMuzzleEffect();

}

void ASniperRifleGun::BeginPlay()
{
	Super::BeginPlay();
	TimeBetweenFire = 60 / ShotOfRate;
}

void ASniperRifleGun::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASniperRifleGun, ProjectileDamage);
	DOREPLIFETIME(ASniperRifleGun, HitScanTrace);
}

void ASniperRifleGun::StartFire()
{
	float FirstDelay = FMath::Max(0.f, LastTimeFire + TimeBetweenFire - GetWorld()->TimeSeconds);
	GetWorldTimerManager().SetTimer(TimerHandle_TimeBetweenShot
		, this
		, &ASniperRifleGun::Fire
		, TimeBetweenFire
		, true
		, FirstDelay
	);
}

void ASniperRifleGun::StopFire()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_TimeBetweenShot);
}

