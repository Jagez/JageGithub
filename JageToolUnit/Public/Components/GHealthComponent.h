// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GHealthComponent.generated.h"

//custom event
DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnHealthChangedSignature, UGHealthComponent*, HealthCoomponent, float, Health, float, DetlaHealth, const class UDamageType*, DamageType, class AController*, InstigatedBy, AActor*, DamageCauser);

UCLASS( ClassGroup=(Jage), meta=(BlueprintSpawnableComponent) )
class JAGETOOLUNIT_API UGHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGHealthComponent();

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHealthChangedSignature OnHealthChanged;

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealth() const { return Health; }

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetMana() const { return Mana; }

	UFUNCTION(BlueprintCallable, Category = "Health")
		float GetDefaultHealth() const { return DefaultHealth; }

	UFUNCTION(BlueprintCallable, Category = "Health")
		float GetDefaultMana() const { return DefaultMana; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Health")
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
	float DefaultHealth;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Health")
	float Mana;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
	float DefaultMana;

private:
	UFUNCTION()
	void OnDamage(AActor* DamagedActor
		, float Damage
		, const class UDamageType* DamageType
		, class AController* InstigatedBy
		, AActor* DamageCauser
	);

		
public:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};
