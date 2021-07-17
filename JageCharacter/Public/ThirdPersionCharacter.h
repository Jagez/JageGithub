// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ThirdPersionCharacter.generated.h"

class UTestUserWidget;

UCLASS()
class JAGECHARACTER_API AThirdPersionCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AThirdPersionCharacter();

	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnAtRate(float Rate);
	void LookAtRate(float Rate);

	void OnStartFire();
	void OnStopFire();

	void BeginCrouch();
	void EndCrouch();
	void BeginAccelerate();
	void EndAccelerate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerFire();
	UFUNCTION(Server, Reliable, WithValidation)
		void ServerStopFire();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//override Pawn.h function,  return eye's location
	virtual FVector GetPawnViewLocation() const override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
private:


private:

	void BeginZoom();
	void EndZoom();

	UFUNCTION()
	void OnHealthChanged(class UGHealthComponent* HealthComp
						, float Health
						, float DetlaHealth
						, const class UDamageType* DamageType
						, class AController* InstigatedBy
						, AActor* DamageCauser);

	UFUNCTION()
	void OnRep_Alive();

public:
	UPROPERTY(VisibleAnywhere, Category = "ThirdPersion")
	class USkeletalMeshComponent* ThirdPersionComp;

	UPROPERTY(VisibleAnywhere, Category = "ThirdPersion")
	class UCameraComponent* ThirdCameraComp;

	UPROPERTY(VisibleAnywhere, Category = "ThirdPersion")
	class USpringArmComponent* ThirdCameraArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ThirdPersion")
	class UGHealthComponent * HealthComponent;

	UPROPERTY(Replicated)
	class ASniperRifleGun * CurrWeapon;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<class ASniperRifleGun> SniperRifleGun;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponSocketName;

	UPROPERTY(Replicated, ReplicatedUsing = "OnRep_Alive", BlueprintReadOnly, Category = "Character")
	bool Alive;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		float BaseTurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		float BaseLookUpRate;

	bool bZoomState;

	UPROPERTY(EditDefaultsOnly, Category = "Zoom")
		float ZoomFOV;		//field of view

	UPROPERTY(EditDefaultsOnly, Category = "Zoom")
		float DefaultFOV;

	UPROPERTY(EditDefaultsOnly, Category = "Zoom")
		float ZoomInterpSpeed;

	UPROPERTY()
	UTestUserWidget *HealthWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<UTestUserWidget> HealthWidgetClass;
};
