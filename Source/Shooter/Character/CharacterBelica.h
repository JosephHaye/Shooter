// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBelica.generated.h"

class AWeapon;

UCLASS()
class SHOOTER_API ACharacterBelica : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBelica();

	UFUNCTION(BlueprintPure)
		bool IsDead() const;

	UFUNCTION(BlueprintPure)
		float GetHealthPercentage() const;

	UFUNCTION(BlueprintPure)
		float GetAmmoPercentage() const;

	//------------------------- Debug code ------------------------//

	//UFUNCTION(BlueprintCallable, Category = "Health")
	//	void Heal(float _HealAmount);

	//UFUNCTION(BlueprintCallable, Category = "Damage")
	//	void Damage(int _DamageAmount);

	//UFUNCTION(BlueprintCallable, Category = "Ammo")
	//	void AddAmmo(int _AmmoAmount);

	//void StartHealing();
	//
	//void StartDamage();

	//void GetAmmo();

	//--------------------------------------------------------//

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(BlueprintReadOnly)
	bool IsPrimaryWeaponSelected = true;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);
	void Shoot();
	void Rifle();
	void GrenadeLauncher();
	void Sprint();
	void NotSprinting();



	UPROPERTY(EditAnywhere)
		float RotationRate = 10;

	UPROPERTY(EditDefaultsOnly)
		float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere)
		float Health;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AWeapon> WeaponClass;

	//UPROPERTY(EditDefaultsOnly)
	//	TArray<TSubclassOf<AWeapon>> Guns;

	UPROPERTY()
		AWeapon* Weapon;
};
