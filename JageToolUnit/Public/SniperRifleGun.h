// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Private/GWeapon.h"
//#include "GWeapon.h"
#include "SniperRifleGun.generated.h"

#define DEFAULT_SNIPERRIFLE_PROJECTILE_DAMAGE 20.f

USTRUCT()
struct FHitScanTrace
{
	GENERATED_BODY()
public:
	UPROPERTY()
		TEnumAsByte<EPhysicalSurface> SurfaceType;
	UPROPERTY()
		FVector_NetQuantize TraceTo;
	UPROPERTY()
		uint8 BurstCounter;
};
/**
 * 
 */
UCLASS()
class JAGETOOLUNIT_API ASniperRifleGun : public AGWeapon
{
	GENERATED_BODY()

public:
	ASniperRifleGun();

	UFUNCTION()
	virtual void Fire();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void StartFire();
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void StopFire();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundBase* FireSound;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
		TSubclassOf<class UCameraShakeBase> CameraShakeClass;

	//shot count by per min.
	float TimeBetweenFire;

	//the rate of weapon fire
	UPROPERTY(EditDefaultsOnly, Category = "Fire")
	float ShotOfRate;
	UPROPERTY()
	float LastTimeFire;

	UPROPERTY()
	FTimerHandle TimerHandle_TimeBetweenShot;

private:
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			FVector NormalImpulse,
			const FHitResult& Hit);


protected:

	UFUNCTION()
	void OnRep_ProjectileDamage();

	UFUNCTION()
	void OnRep_HitScanTrace();

	UPROPERTY(ReplicatedUsing = "OnRep_ProjectileDamage")
	float ProjectileDamage;

	void BeginPlay() override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<class ASniperRifleProjectile> ProjectileClass;
	
	UPROPERTY(ReplicatedUsing = "OnRep_HitScanTrace")
		FHitScanTrace HitScanTrace;
	//Ëæ»úÇ¹¿Ú½Ç¶ÈÆ«ÒÆ
	UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (ClamMin = 0.f))
		float BulletSpread;
};
