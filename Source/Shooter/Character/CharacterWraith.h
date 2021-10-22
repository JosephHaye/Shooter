// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterWraith.generated.h"

class AWeapon;

UCLASS()
class SHOOTER_API ACharacterWraith : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterWraith();

	UFUNCTION(BlueprintPure)
		bool AIIsDead() const;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void AIShoot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditDefaultsOnly)
		float AIMaxHealth = 100;

	UPROPERTY(VisibleAnywhere)
		float AIHealth;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AWeapon> WeaponClass;

	UPROPERTY()
		AWeapon* AIWeapon;

};
