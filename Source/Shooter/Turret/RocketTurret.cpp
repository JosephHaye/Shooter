// Fill out your copyright notice in the Description page of Project Settings.


#include "RocketTurret.h"
#include <Kismet/GameplayStatics.h>
#include "Shooter/Character/CharacterBelica.h"
#include "Shooter/ShooterGameMode.h"
#include "Projectile.h"

ARocketTurret::ARocketTurret()
{

}

// Called every frame
void ARocketTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PlayerPawn || ReturnDistanceToPlayer() > FireRange)
	{
		return;
	}

	RotateTurretFunction(PlayerPawn->GetActorLocation());
}

void ARocketTurret::CheckFireCondition()
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


float ARocketTurret::ReturnDistanceToPlayer()
{
	if (!PlayerPawn)
	{
		return 0.0f;
	}

	float Distance = FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
	return Distance;
}

// Called when the game starts or when spawned
void ARocketTurret::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &ARocketTurret::CheckFireCondition, FireRate, true);

	PlayerPawn = Cast<ACharacterBelica>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void ARocketTurret::Fire()
{
	if (ProjectileClass)
	{
		FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();

		AProjectile* TempProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
		TempProjectile->SetOwner(this);
	}
	//Debug to check fire condition works
	UE_LOG(LogTemp, Warning, TEXT("Fire Condition Checked"));
}

// Applies damage
float ARocketTurret::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	// Applies Damage based on each weapon
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;

	// Debug code
	//UE_LOG(LogTemp, Warning, TEXT("Health left %f"), Health);

	if (IsDead())
	{
		AShooterGameMode* GameMode = GetWorld()->GetAuthGameMode<AShooterGameMode>();
		if (GameMode != nullptr)
		{
			GameMode->PawnKilled(this);
		}

		Destroy();
	}

	return DamageToApply;
}

bool ARocketTurret::IsDead() const
{
	return Health <= 0;
}