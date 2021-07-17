// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GWeapon.generated.h"

#define SURFACE_FLESHDEFAULT		SurfaceType1
#define SURFACE_FLESHVULENRABLE		SurfaceType2
#define DEFAULT_MUZZLE_SOCKET_NAME	"MuzzleSocket"
#define DEFAULT_AMMO_SOCKET_NAME	"AmmoSocket"

class UDamageType;

UCLASS()
class AGWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Fire();

	virtual void StartFire();
	virtual void StopFire();

	virtual void PlayImpactEffect(EPhysicalSurface PhySurface, FVector ImpactPoint);
	virtual void PlayMuzzleEffect();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	class USkeletalMeshComponent* WeaponComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName MuzzleSocketName;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName AmmoSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	TSubclassOf<UDamageType> DamageType;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect")
	class UParticleSystem* MuzzleEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect")
	class UParticleSystem* DefaultImpactEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect")
	class UParticleSystem* FleshImpactEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect")
	class UParticleSystem* TargetImpactEffect;

	UPROPERTY(BlueprintReadOnly, Category = "Muzzle")
	FVector MuzzleLocation;

	UPROPERTY(BlueprintReadOnly, Category = "Muzzle")
	FRotator MuzzleRotation;

	UPROPERTY(BlueprintReadOnly, Category = "Muzzle")
	FVector EyeLocation;

};
