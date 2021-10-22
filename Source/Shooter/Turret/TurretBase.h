// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TurretBase.generated.h"

class UCapsuleComponent;

UCLASS()
class SHOOTER_API ATurretBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATurretBase();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAcces = "True"))
		UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAcces = "True"))
		UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAcces = "True"))
		UStaticMeshComponent* Turret;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAcces = "True"))
		USceneComponent* ProjectileSpawnPoint;

	void RotateTurretFunction(FVector LookAtTarget);


};
