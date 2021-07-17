// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupActor.h"
#include "JageProjectCharacter.h"
#include "JageProjectGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
APickupActor::APickupActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//create component
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("MeshComponent")));
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);		//close collision
	RootComponent = MeshComponent;		//set RootComponent;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(FName(TEXT("SphereComponent")));
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	SphereComponent->SetupAttachment(MeshComponent);

	/**
	*		
	*/
	TArray<UPrimitiveComponent*> PrimitiveComponentArr;
	SphereComponent->GetOverlappingComponents(PrimitiveComponentArr);
	for (UPrimitiveComponent* priComp : PrimitiveComponentArr)
	{
		const float Radius = SphereComponent->GetScaledSphereRadius();
		const float ForceStrength = -2000.f;
		priComp->AddRadialForce(GetActorLocation(), Radius, ForceStrength,
			ERadialImpulseFalloff::RIF_Linear, true);
	}

}

// Called when the game starts or when spawned
void APickupActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickupActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickupActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	AJageProjectCharacter* Charactor = Cast<AJageProjectCharacter>(OtherActor);
	if (nullptr != Charactor)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString(TEXT("pickup")));
		AJageProjectGameMode * GameMode = Cast<AJageProjectGameMode>(GetWorld()->GetAuthGameMode());
		if (nullptr != GameMode)
		{
			//game completed.
			GameMode->Completed();
		}
	}

}

