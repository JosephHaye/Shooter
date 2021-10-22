// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBelica.h"
#include "Shooter/Weapon/Weapon.h"
#include "Shooter/ShooterGameMode.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ACharacterBelica::ACharacterBelica()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACharacterBelica::BeginPlay()
{
	Super::BeginPlay();

	// Sets Health as MaxHealth
	Health = MaxHealth;

	// Spawns Weapon
	Weapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass);
	GetMesh()->HideBoneByName(TEXT("weapon"), EPhysBodyOp::PBO_None);
	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("weaponSocket"));
	Weapon->SetOwner(this);
	
}

// Calls IsDead Animation
bool ACharacterBelica::IsDead() const
{
	return Health <= 0;
}
// Gets the amount of Health left
float ACharacterBelica::GetHealthPercentage() const
{
	return Health / MaxHealth;
}

// Gets the amount of Ammo left
float ACharacterBelica::GetAmmoPercentage() const
{
	return Weapon->GetAmmo();
}

// Adds Health
void ACharacterBelica::Heal(float _HealAmount)
{
	UE_LOG(LogTemp, Warning, TEXT("We are healing for %f points."), _HealAmount);
	Health += _HealAmount;

	if (Health > 100)
	{
		Health = 100;
	}
}

// Adds Ammo 
void ACharacterBelica::AddAmmo(int _AmmoAmount)
{
	Weapon->AddAmmo(_AmmoAmount);

	UE_LOG(LogTemp, Warning, TEXT("You have gained %f Ammo."), _AmmoAmount);
}

// Debug to check if healing works
//void ACharacterBelica::StartHealing()
//{
//	Heal(0.02f);
//}

// Called every frame
void ACharacterBelica::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterBelica::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Allows player to move forward and back
	// Allows player to look up and down
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ACharacterBelica::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);

	// Allows player to move right and left
	// Allows player to look right to left
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ACharacterBelica::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);

	// Allows the player to use their controller
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &ACharacterBelica::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &ACharacterBelica::LookRightRate);

	// Allows the player to Jump
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);

	// Allows for player to heal using a button press
	//PlayerInputComponent->BindAction(TEXT("Heal"), IE_Pressed, this, &ACharacterBelica::StartHealing);

	// Allows the player to Shoot
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &ACharacterBelica::Shoot);
}

// Applies damage
float ACharacterBelica::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
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

		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	}

	return DamageToApply;
}

void ACharacterBelica::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void ACharacterBelica::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void ACharacterBelica::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void ACharacterBelica::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

// Calls PullTrigger
void ACharacterBelica::Shoot()
{
	Weapon->PullTrigger();
}