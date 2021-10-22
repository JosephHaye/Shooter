// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterWraith.h"
#include "Shooter/Weapon/Weapon.h"
#include "Shooter/ShooterGameMode.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ACharacterWraith::ACharacterWraith()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACharacterWraith::BeginPlay()
{
	Super::BeginPlay();
	
	//Sets AIHealth as AIMaxHealth
	AIHealth = AIMaxHealth;

	//Spawns Weapon
	AIWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	AIWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("weapon_rSocket"));
	AIWeapon->SetOwner(this);

}

// Called every frame
void ACharacterWraith::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Calls AIIsDead Animation
bool ACharacterWraith::AIIsDead() const
{
	return AIHealth <= 0;
}

// Applies damage
float ACharacterWraith::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	//Applies Damage based on each weapon
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(AIHealth, DamageToApply);
	AIHealth -= DamageToApply;

	if (AIIsDead())
	{
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		AShooterGameMode* GameMode = GetWorld()->GetAuthGameMode<AShooterGameMode>();
		if (GameMode != nullptr)
		{
			GameMode->PawnKilled(this);
		}
	}

	return DamageToApply;
}

// Calls PullTrigger
void ACharacterWraith::AIShoot()
{
	AIWeapon->PullTrigger();
}