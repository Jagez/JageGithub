// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/GHealthComponent.h"
#include "JageProjectGameMode.h"
#include "UnrealNetwork.h"

// Sets default values for this component's properties
UGHealthComponent::UGHealthComponent()
{
	DefaultHealth	= 100;
	DefaultMana		= 100;
	SetIsReplicated(true);
}


// Called when the game starts
void UGHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwnerRole() == ROLE_Authority)
	{
		AActor* GOwner = GetOwner();
		if (nullptr != GOwner)
		{
			GOwner->OnTakeAnyDamage.AddDynamic(this, &UGHealthComponent::OnDamage);
		}
	}
	Health = DefaultHealth;

	
}

void UGHealthComponent::OnDamage(AActor* DamagedActor
	, float Damage
	, const class UDamageType* DamageType
	, class AController* InstigatedBy
	, AActor* DamageCauser)
{
	if (Damage <= 0.f)
	{
		return;
	}
	Health = FMath::Clamp(Health - Damage, 0.f, DefaultHealth);

	OnHealthChanged.Broadcast(this, Health, Damage, DamageType, InstigatedBy, DamageCauser);
	Cast<AJageProjectGameMode>(GetWorld()->GetAuthGameMode());
}

void UGHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UGHealthComponent, Health);
	DOREPLIFETIME(UGHealthComponent, Mana);
}

