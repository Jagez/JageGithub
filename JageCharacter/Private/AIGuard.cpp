// Fill out your copyright notice in the Description page of Project Settings.


#include "AIGuard.h"
#include "Perception/PawnSensingComponent.h"		// must add "AIModule" Plugin into Build.cs
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AAIGuard::AAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	//server only
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AAIGuard::SeePawnCallback);		//call SeePawnCallback function when has been see target
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AAIGuard::NoiseHeardCallback);   //call NoiseHeardCallback function when has been heard target
}

void AAIGuard::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AAIGuard, GuardState);
	//DOREPLIFETIME_CONDITION(AAIGuard, GuardState, COND_OwnerOnly);	//replicate by COND_OwnerOnly condition
}

// Called when the game starts or when spawned
void AAIGuard::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAIGuard::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAIGuard::SeePawnCallback(APawn* Pawn)
{
	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT(" Found army."));
	//control movemention
	AController* Controller = GetController();
	if (nullptr != Controller)
	{
		//Controller->StopMovement();

		/**
		*	OnRep_ReplicateMovement: 调用client端更新movement
		*	OnRep_ReplicatedMovement:	
		*/
		Controller->OnRep_ReplicatedMovement();
		
	}
}

void AAIGuard::NoiseHeardCallback(APawn* InstigatorPawn, const FVector& Location, float Volume)
{
	if (FirstActor != nullptr)
	{
		MoveToNextActor(FirstActor);
	}
	MoveToNextActor(InstigatorPawn->GetOwner());
}

float AAIGuard::MoveToNextActor(AActor* Target)
{
	UAIBlueprintHelperLibrary::SimpleMoveToActor(GetController(), Target);
	return 0.0f;
}

void AAIGuard::OnRep_State()
{
}

