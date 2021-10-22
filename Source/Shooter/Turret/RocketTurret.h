// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurretBase.h"
#include "RocketTurret.generated.h"

class ACharacterBelica;
class AProjectile;

UCLASS()
class SHOOTER_API ARocketTurret : public ATurretBase
{
	GENERATED_BODY()
	
public:

	// Sets default values for this property
	ARocketTurret();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess));
	float FireRate = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess));
	float FireRange = 500.0f;

	UPROPERTY(EditDefaultsOnly)
		float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere)
		float Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile Type", meta = (AllowPrivateAcces = "True"))
	TSubclassOf<AProjectile> ProjectileClass;

	UFUNCTION(BlueprintPure)
		bool IsDead() const;

	void Fire();

private:

	void CheckFireCondition();

	FTimerHandle FireRateTimerHandle;

	ACharacterBelica* PlayerPawn;

	float ReturnDistanceToPlayer();
};
