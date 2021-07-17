// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShotGunWeapon.generated.h"

class UDamageType;

UCLASS()
class JAGETOOLUNIT_API AShotGunWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShotGunWeapon();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ShotGun")
	class USkeletalMeshComponent* ShotGunComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	TSubclassOf<UDamageType> DamageType;


	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "ShotGun")
		FName MuzzleSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ShotGun")
		class UParticleSystem* MuzzleEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ShotGun")
		class UParticleSystem* ImpactEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ShotGun")
	class UParticleSystem* TracerEffect;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "ShotGun")
	virtual void Fire();

};
