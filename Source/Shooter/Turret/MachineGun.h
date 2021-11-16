// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MachineGun.generated.h"

UCLASS()
class SHOOTER_API AMachineGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMachineGun();

	void Shoot();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	

	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
		UParticleSystem* MuzzleFlash;

	//UPROPERTY(EditAnywhere)
	//	USoundBase* MuzzleSoundEffect;

	//UPROPERTY(EditAnywhere)
	//	USoundBase* MuzzleEmptyEffect;

	//UPROPERTY(EditAnywhere)
	//	USoundBase* Impact;

	UPROPERTY(EditAnywhere)
		UParticleSystem* ImpactEffect;

	UPROPERTY(EditAnywhere)
		float MaxRange = 5000;

	UPROPERTY(EditAnywhere)
		float Damage = 10;

	bool TurretTraceCode(FHitResult& Hit, FVector& ShotDirection);

	AController* GetOwnerController() const;
};
