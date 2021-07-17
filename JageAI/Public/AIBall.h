// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "AIBall.generated.h"

UCLASS()
class JAGEAI_API AAIBall : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAIBall();

	FVector GetNextNavPathPoint();

public:
	class UMaterialInstanceDynamic* LowHeallthMatInst;


	void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp
			, AActor* OtherActor
			, UPrimitiveComponent* OtherComp
			, FVector NormalImpulse
			, const FHitResult& Hit
		);

	UFUNCTION()
		void OnHealthChanged(class UGHealthComponent* HealthCoomponent
			, float Health
			, float DetlaHealth
			, const class UDamageType* DamageType
			, class AController* InstigatedBy
			, AActor* DamageCauser);

	UFUNCTION()
	void SelfDestruct();

protected:
	UPROPERTY()
		FVector NavPathNextPoint;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		float DistanceOfTarget;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Physics")
	float ForceImpluse;

	UPROPERTY(EditDefaultsOnly, Category = "Physics")
	bool IsVelocityChanged;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UGHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
	class UParticleSystem* ExplosionEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
	class USoundCue* SelfDestructSound;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
	class USoundCue* ExplodeSound;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float ExplosionDamage;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float ExplosionRadius;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
