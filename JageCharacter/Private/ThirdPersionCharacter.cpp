// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdPersionCharacter.h"
#include "GToolCommon.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include <Engine/World.h>
#include "SniperRifleGun.h"
#include "Components/GHealthComponent.h"
#include "Components/ProgressBar.h"
#include "TestUserWidget.h"
#include "Net/UnrealNetwork.h"

static int32 DebugVar = 0;
FAutoConsoleVariableRef CVRDebugVar(
	TEXT("Jage.DebugVar"),
	DebugVar,
	TEXT("Use the console to control variable values"),
	ECVF_Cheat
);

// Sets default values
AThirdPersionCharacter::AThirdPersionCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ThirdPersionComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ThirdPersionComp"));
	ThirdPersionComp->SetOnlyOwnerSee(false);
	ThirdPersionComp->SetupAttachment(RootComponent);
	ThirdPersionComp->bReturnMaterialOnMove = true;

	ThirdCameraArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("ThirdCameraArmComp"));
	ThirdCameraArmComp->SetupAttachment(RootComponent);
	ThirdCameraArmComp->bUsePawnControlRotation = true;		//PlayerController control the SpringArm


	ThirdCameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdCamerComp"));
	ThirdCameraComp->SetupAttachment(ThirdCameraArmComp);

	HealthComponent = CreateDefaultSubobject<UGHealthComponent>(TEXT("HealthComponent"));

	BaseTurnRate = 30.f;
	BaseLookUpRate = 30.f;
	bZoomState = false;
	ZoomFOV = 65.f;
	ZoomInterpSpeed = 20.f;
	WeaponSocketName = "Weapon_socket";
	Alive = true;

	//can Crouch
	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(COLLISION_CHANNEL, ECollisionResponse::ECR_Ignore);

	SetReplicates(true);
	SetReplicatingMovement(true);

}

void AThirdPersionCharacter::MoveForward(float Value)
{
	if (Value != 0.f)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AThirdPersionCharacter::MoveRight(float Value)
{
	if (Value != 0.f)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}



void AThirdPersionCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AThirdPersionCharacter::LookAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AThirdPersionCharacter::OnStartFire()
{
	if (nullptr != CurrWeapon)
	{
		if (GetLocalRole() < ROLE_Authority)
		{
			ServerFire();
		}
		CurrWeapon->StartFire();
	}
	
}

void AThirdPersionCharacter::OnStopFire()
{
	if (nullptr != CurrWeapon)
	{
		if (GetLocalRole() < ROLE_Authority)
		{
			ServerStopFire();
		}
		CurrWeapon->StopFire();
	}
}

void AThirdPersionCharacter::BeginCrouch()
{
	Crouch();
}

void AThirdPersionCharacter::EndCrouch()
{
	UnCrouch();
}

void AThirdPersionCharacter::BeginAccelerate()
{
	GetCharacterMovement()->MaxWalkSpeed = 1000.f;
}

void AThirdPersionCharacter::EndAccelerate()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
}

// Called when the game starts or when spawned
void AThirdPersionCharacter::BeginPlay()
{
	Super::BeginPlay();

	HealthWidget = CreateWidget<UTestUserWidget>(GetWorld(), HealthWidgetClass);
	if (nullptr != HealthWidget)
	{
		HealthWidget->AddToViewport();
		//HealthWidget->HPBar->SetPercent(HealthComponent->GetHealth());
		//HealthWidget->ManaBar->SetPercent(HealthComponent->GetMana());
	}

	HealthComponent->OnHealthChanged.AddDynamic(this, &AThirdPersionCharacter::OnHealthChanged);

	UWorld* TempWorld = GetWorld();
	if (nullptr != TempWorld && GetLocalRole() == ROLE_Authority)
	{
		FActorSpawnParameters SpawnParameters;
		FVector WeaponLocation = GetActorLocation();
		FRotator WeaponRatation = GetControlRotation();
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		SpawnParameters.Instigator = this;
		if (SniperRifleGun != nullptr)
		{
			CurrWeapon = TempWorld->SpawnActor<ASniperRifleGun>(SniperRifleGun, WeaponLocation, WeaponRatation, SpawnParameters);
			//FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
			if (nullptr != CurrWeapon)
			{
				CurrWeapon->SetOwner(this);
				CurrWeapon->AttachToComponent(GetMesh()
					, FAttachmentTransformRules::SnapToTargetNotIncludingScale
					, WeaponSocketName);
			}
		}
	}

	//Default camera FOV
	DefaultFOV = ThirdCameraComp->FieldOfView;
	
}

void AThirdPersionCharacter::ServerFire_Implementation()
{
	OnStartFire();
}

bool AThirdPersionCharacter::ServerFire_Validate()
{
	return true;
}

void AThirdPersionCharacter::ServerStopFire_Implementation()
{
	OnStopFire();
}

bool AThirdPersionCharacter::ServerStopFire_Validate()
{
	return true;
}

// Called every frame
void AThirdPersionCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/* Set camera FOV */
	float TargetFOV = bZoomState ? ZoomFOV : DefaultFOV;
	float NewFOV = FMath::FInterpTo(ThirdCameraComp->FieldOfView, TargetFOV, DeltaTime, ZoomInterpSpeed);
	ThirdCameraComp->SetFieldOfView(NewFOV);
}

// Called to bind functionality to input
void AThirdPersionCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AThirdPersionCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AThirdPersionCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AThirdPersionCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AThirdPersionCharacter::LookAtRate);


	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AThirdPersionCharacter::OnStartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AThirdPersionCharacter::OnStopFire);

	// Bind Crouch event
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AThirdPersionCharacter::BeginCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AThirdPersionCharacter::EndCrouch);

	// Bind Zoom event
	PlayerInputComponent->BindAction("Zoom", IE_Pressed, this, &AThirdPersionCharacter::BeginZoom);
	PlayerInputComponent->BindAction("Zoom", IE_Released, this, &AThirdPersionCharacter::EndZoom);

	// Bind Accelerate event
	PlayerInputComponent->BindAction("Accelerate", IE_Pressed, this, &AThirdPersionCharacter::BeginAccelerate);
	PlayerInputComponent->BindAction("Accelerate", IE_Released, this, &AThirdPersionCharacter::EndAccelerate);


}

FVector AThirdPersionCharacter::GetPawnViewLocation() const
{
	if (ThirdCameraComp != nullptr)
	{
		return ThirdCameraComp->GetComponentLocation();
	}
	return Super::GetPawnViewLocation();
}

void AThirdPersionCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AThirdPersionCharacter, CurrWeapon);
	DOREPLIFETIME(AThirdPersionCharacter, Alive);
}

void AThirdPersionCharacter::BeginZoom()
{
	bZoomState = true;
}

void AThirdPersionCharacter::EndZoom()
{
	bZoomState = false;
}

void AThirdPersionCharacter::OnHealthChanged(UGHealthComponent* HealthComp
					, float Health, float DetlaHealth
					, const class UDamageType* DamageType
					, class AController* InstigatedBy
					, AActor* DamageCauser)
{
	if (!Alive) return;
	//if health is zero, stop movement
	if (Health <= 0.f && Alive)
	{
		Alive = false;
		GetMovementComponent()->StopMovementImmediately();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		//Call this function to detach safely pawn from its controller, knowing that we will be destroyed soon.
		DetachFromControllerPendingDestroy();
		SetLifeSpan(20.f);
	}

	if (nullptr != HealthWidget)
	{
		HealthWidget->HPBar->SetPercent(Health / 100);
		HealthWidget->ManaBar->SetPercent(HealthComp->GetMana() / 100);
	}
}

void AThirdPersionCharacter::OnRep_Alive()
{

}

