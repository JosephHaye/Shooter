// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class SHOOTER_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	void PullTrigger();

	UFUNCTION(BlueprintPure)
		float GetAmmo() const;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Ammo")
		void AddAmmo(int _AmmoAmount);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* Mesh;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:

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

	UPROPERTY(EditDefaultsOnly)
		int MaxAmmo = 100;

	UPROPERTY(VisibleAnywhere)
		int Ammo;

	bool WeaponTraceCode(FHitResult& Hit, FVector& ShotDirection);

	AController* GetOwnerController() const;
};
