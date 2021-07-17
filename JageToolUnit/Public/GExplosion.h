// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GExplosion.generated.h"

UCLASS()
class JAGETOOLUNIT_API AGExplosion : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGExplosion();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Explosion")
		class UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditDefaultsOnly, Category = "Explosion")
		class URadialForceComponent* RadialForceComp;

	UPROPERTY(EditDefaultsOnly, Category = "Explosion")
		class UGHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Explosion")
		float ExplosionRadius;

	UPROPERTY(EditDefaultsOnly, Category = "Explosion")
		float ExplosionImpulse;

	UPROPERTY(EditDefaultsOnly, Category = "Explosion")
		class UParticleSystem* ExplosionEffect;

private:

	UFUNCTION()
		void OnHealthChanged(class UGHealthComponent* HealthCoomponent
			, float Health
			, float DetlaHealth
			, const class UDamageType* DamageType
			, class AController* InstigatedBy
			, AActor* DamageCauser);


};
