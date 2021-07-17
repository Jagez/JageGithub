// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AICharacter.h"
#include "AIGuard.generated.h"

UENUM(BlueprintType)
enum EAI_State
{
	E_STATE_Idle,
	E_STATE_Dead
};

UCLASS()
class JAGECHARACTER_API AAIGuard : public AAICharacter
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	AAIGuard();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	UPROPERTY(VisibleAnywhere, Category = "AIGuard")
	class UPawnSensingComponent* PawnSensingComp;

	UPROPERTY(EditInstanceOnly, Category = "AIGuard")
		AActor* FirstActor;
	UPROPERTY(EditInstanceOnly, Category = "AIGuard")
		AActor* SecondActor;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UFUNCTION()
	void SeePawnCallback(APawn* Pawn);

	UFUNCTION()
		void NoiseHeardCallback(APawn* InstigatorPawn, const FVector& Location, float Volume);

protected:
	UFUNCTION()
		float MoveToNextActor(AActor* Point);
	UFUNCTION()
		void OnRep_State();

protected:
	//OnRep_State function will be called when the var has replicated
	UPROPERTY(ReplicatedUsing = "OnRep_State")	//using ReplicatedUsing, Remember to add a definition, no need to declare
	TEnumAsByte<enum EAI_State> GuardState;
};
