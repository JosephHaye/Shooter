// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretBase.h"
#include <Components/CapsuleComponent.h>

// Sets default values
ATurretBase::ATurretBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collision"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	Turret = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret"));
	Turret->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(Turret);

}

void ATurretBase::RotateTurretFunction(FVector LookAtTarget)
{

	FVector LookAtTargetClean = FVector(LookAtTarget.X, LookAtTarget.Y, Turret->GetComponentLocation().Z);
	FVector StartLocation = Turret->GetComponentLocation();

	FRotator TurretRotation = FVector(LookAtTargetClean - StartLocation).Rotation();
	Turret->SetWorldRotation(TurretRotation);

}