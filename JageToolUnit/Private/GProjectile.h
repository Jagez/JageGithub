// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GProjectile.generated.h"

UCLASS(config=Game)
class AGProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGProjectile();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			FVector NormalImpulse,
			const FHitResult& Hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetProjectileMaxSpeed(float MaxSpeed);
	void SetProjectileInitSpeed(float InitSpeed);
	void SetVelocitySpeed(bool bVelocity);
	void SetBounce(bool bBounce);

private:
	float MaxProjectileSpeed;
	float InitProjectileSpeed;
	bool bVelocitySpeed;
	bool bProjectileBounce;

	UPROPERTY()
	float Damage;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SetDamage(float Value);
	

protected:

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* ProjectileMovement;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
		class USphereComponent* CollisionComponent;



};
