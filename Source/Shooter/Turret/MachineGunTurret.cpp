// Fill out your copyright notice in the Description page of Project Settings.


#include "MachineGunTurret.h"
#include "Shooter/Character/CharacterBelica.h"
#include "Shooter/Turret/MachineGun.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include <Components/CapsuleComponent.h>

// Sets default values
AMachineGunTurret::AMachineGunTurret()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collision"));
	RootComponent = CapsuleComp;

	Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	Base->SetupAttachment(RootComponent);

	Turret = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret"));
	Turret->SetupAttachment(Base);

}

// Called when the game starts or when spawned
void AMachineGunTurret::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &AMachineGunTurret::CheckFireCondition, FireRate, true);

	Weapon = GetWorld()->SpawnActor<AMachineGun>(WeaponClass);
	Weapon->AttachToComponent(Base, FAttachmentTransformRules::KeepRelativeTransform, TEXT("weaponSocket"));
	Weapon->SetOwner(this);

	PlayerPawn = Cast<ACharacterBelica>(UGameplayStatics::GetPlayerPawn(this, 0));
}

// Called every frame
void AMachineGunTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PlayerPawn || ReturnDistanceToPlayer() > FireRange)
	{
		return;
	}

	RotateTurretFunction(PlayerPawn->GetActorLocation());
}

void AMachineGunTurret::RotateTurretFunction(FVector LookAtTarget)
{

	FVector LookAtTargetClean = FVector(LookAtTarget.X, LookAtTarget.Y, Base->GetComponentLocation().Z);
	FVector StartLocation = Base->GetComponentLocation();

	FRotator TurretRotation = FVector(LookAtTargetClean - StartLocation).Rotation();
	Base->SetWorldRotation(TurretRotation);

}

void AMachineGunTurret::CheckFireCondition()
{
	if (!PlayerPawn)
	{
		return;
	}

	if (ReturnDistanceToPlayer() <= FireRange)
	{
		Fire();
	}

}

float AMachineGunTurret::ReturnDistanceToPlayer()
{
	if (!PlayerPawn)
	{
		return 0.0f;
	}

	float Distance = FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
	return Distance;
}

void AMachineGunTurret::Fire()
{
	Weapon->Shoot();
}
