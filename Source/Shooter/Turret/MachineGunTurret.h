// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurretBase.h"
#include "MachineGunTurret.generated.h"

class ACharacterBelica;
class AMachineGun;
class UCapsuleComponent;

UCLASS()
class SHOOTER_API AMachineGunTurret : public APawn
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AMachineGunTurret();

	void Fire();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat");
	float FireRate = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat");
	float FireRange = 500.0f;

	UPROPERTY(VisibleAnywhere)
		UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Base;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Turret;

	void RotateTurretFunction(FVector LookAtTarget);

private:

	void CheckFireCondition();

	float ReturnDistanceToPlayer();

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AMachineGun> WeaponClass;

	UPROPERTY()
		AMachineGun* Weapon;

	FTimerHandle FireRateTimerHandle;

	ACharacterBelica* PlayerPawn;
};
