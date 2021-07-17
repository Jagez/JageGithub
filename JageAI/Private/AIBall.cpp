// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBall.h"
#include "Components/SphereComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/GHealthComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem/Public/NavigationPath.h"
#include "NavigationSystem/Public/NavigationSystem.h"
#include "Sound/SoundCue.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

// Sets default values
AAIBall::AAIBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ForceImpluse = 400.f;
	ExplosionDamage = 100.f;
	ExplosionRadius = 200.f;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	if (nullptr != MeshComponent)
	{
		MeshComponent->SetSimulatePhysics(true);
		MeshComponent->SetCanEverAffectNavigation(false);		//不影响导航
		MeshComponent->OnComponentHit.AddDynamic(this, &AAIBall::OnHit);

		RootComponent = MeshComponent;
	}

	HealthComponent = CreateDefaultSubobject<UGHealthComponent>(TEXT("HealthComponent"));
}

FVector AAIBall::GetNextNavPathPoint()
{
	ACharacter* PlayerPawn = UGameplayStatics::GetPlayerCharacter(this, 0);
	UNavigationPath* NavPath = UNavigationSystemV1::FindPathToActorSynchronously(this, GetActorLocation(), PlayerPawn);
	TArray<FVector> PathPoints = NavPath->PathPoints;
	if (PathPoints.Num() > 1)
	{
		for (FVector var : PathPoints)
		{
			
			DrawDebugSphere(GetWorld(), var, 20.f, 2, FColor::Yellow);
		}
		return PathPoints[1];
	}
	else
	{
		return GetActorLocation();
	}
}

void AAIBall::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	ACharacter* OwnerCharacter = Cast<ACharacter>(OtherActor);
	if (nullptr != OwnerCharacter)
	{
		//UGameplayStatics::ApplyPointDamage(this, GetActorLocation(),)
	}
	if (nullptr != SelfDestructSound)
	{
		UGameplayStatics::SpawnSoundAttached(SelfDestructSound, RootComponent);
	}
}

// Called when the game starts or when spawned
void AAIBall::BeginPlay()
{
	Super::BeginPlay();

	if (nullptr != HealthComponent)
	{
		HealthComponent->OnHealthChanged.AddDynamic(this, &AAIBall::OnHealthChanged);
	}
	UAIBlueprintHelperLibrary::SimpleMoveToActor(GetController(), UGameplayStatics::GetPlayerPawn(this, 0));
	//MeshComponent->AddImpulse()

}

void AAIBall::OnHit(UPrimitiveComponent* HitComp
	, AActor* OtherActor
	, UPrimitiveComponent* OtherComp
	, FVector NormalImpulse
	, const FHitResult& Hit) 
{

}

void AAIBall::OnHealthChanged(class UGHealthComponent* HealthComp
	, float Health, float DetlaHealth
	, const class UDamageType* DamageType
	, class AController* InstigatedBy
	, AActor* DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("%f"), Health));
	if (0.f >= Health)
	{
		SelfDestruct();
	}

	if (nullptr != LowHeallthMatInst)
	{
		LowHeallthMatInst->SetScalarParameterValue("LastTime", GetWorld()->TimeSeconds);
	}
	else
	{
		//从组件中获取材质索引为0的材质
		LowHeallthMatInst = MeshComponent->CreateAndSetMaterialInstanceDynamicFromMaterial(0
			, MeshComponent->GetMaterial(0));
	}


}

void AAIBall::SelfDestruct()
{
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(this);

	if (nullptr != ExplodeSound && nullptr != ExplosionEffect)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplodeSound, GetActorLocation());
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());
	}

	UGameplayStatics::ApplyRadialDamage(this
		, ExplosionDamage
		, GetActorLocation()
		, ExplosionRadius
		, nullptr
		, IgnoreActors
		, this
		, GetInstigatorController()
		, true
	);

	Destroy(true);
}

// Called every frame
void AAIBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float DistanceToTarget = (NavPathNextPoint - GetActorLocation()).Size();
	if (DistanceToTarget > DistanceOfTarget)
	{
		FVector Direction = NavPathNextPoint - GetActorLocation();
		Direction.Normalize();
		Direction *= ForceImpluse;
		MeshComponent->ComponentVelocity.Size();
		MeshComponent->AddImpulse(Direction, NAME_None, IsVelocityChanged);
		
	}
	else
	{
		NavPathNextPoint = GetNextNavPathPoint();
		//DrawDebugString();
	}
	DrawDebugSphere(GetWorld(), NavPathNextPoint, 20.f, 12, FColor::Blue, false, 5.f, 0, 1.f);
}

