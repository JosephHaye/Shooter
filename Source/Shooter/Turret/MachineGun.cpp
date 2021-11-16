// Fill out your copyright notice in the Description page of Project Settings.


#include "MachineGun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AMachineGun::AMachineGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Sets up the root
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	// Sets up the mesh
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void AMachineGun::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMachineGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMachineGun::Shoot()
{
	// States player has been shot when trigger is pressed
	//UE_LOG(LogTemp, Warning, TEXT("You've been shot!"));

	// Sets the emitter for the weapon
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));


	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return;

	AController* OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr) return;

	FVector Location;
	FRotator Rotation;

	OwnerController->GetPlayerViewPoint(Location, Rotation);

	//DrawDebugCamera(GetWorld(), Location, Rotation, 90, 20, FColor::Red, true);

	FVector End = Location + Rotation.Vector() * MaxRange;

	FHitResult Hit;
	
	// Ignores Owner
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	
	bool bSuccess = GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);

	if (bSuccess)
	{
		DrawDebugPoint(GetWorld(), Hit.Location, 20, FColor::Red, true);
	}
	
//	// Sets hit and shot direction
//	FHitResult Hit;
//	FVector ShotDirection;
//
//	// Sets bSuccess to call WeaponTraceCode
//	bool bSuccess = TurretTraceCode(Hit, ShotDirection);
//
//	// Sets the sound attached to the weapon
//	//UGameplayStatics::SpawnSoundAttached(MuzzleSoundEffect, SpawnPoint, TEXT("MuzzleFlashSocket"));
//
//	if (bSuccess)
//	{
//		// Spawns ImpactEffect at Location
//		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation());
//
//		// Spawns Impact sound at Location
//		//UGameplayStatics::PlaySoundAtLocation(GetWorld(), Impact, Hit.Location);
//
//		// Applies emitter and damage
//		AActor* HitActor = Hit.GetActor();
//
//		if (HitActor != nullptr)
//		{
//			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
//			AController* OwnerController = GetOwnerController();
//			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
//		}
//	}
}
//
//// Called for line trace
//bool AMachineGun::TurretTraceCode(FHitResult& Hit, FVector& ShotDirection)
//{
//	AController* OwnerController = GetOwnerController();
//	if (OwnerController == nullptr)
//		return false;
//
//	// Sets Vector and Rotation
//	FVector Location;
//	FRotator Rotation;
//
//	// Gets player camera location and rotation
//	OwnerController->GetPlayerViewPoint(Location, Rotation);
//
//	ShotDirection = -Rotation.Vector();
//
//	// Finds the end point
//	FVector End = Location + Rotation.Vector() * MaxRange;
//
//	// Ignores Owner
//	FCollisionQueryParams Params;
//	Params.AddIgnoredActor(this);
//	Params.AddIgnoredActor(GetOwner());
//
//	return  GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
//
//}
//
//AController* AMachineGun::GetOwnerController() const
//{
//	APawn* OwnerPawn = Cast<APawn>(GetOwner());
//	if (OwnerPawn == nullptr)
//		return nullptr;
//
//	return  OwnerPawn->GetController();
//
//}