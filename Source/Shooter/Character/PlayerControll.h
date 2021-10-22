// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControll.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API APlayerControll : public APlayerController
{
	GENERATED_BODY()
	
public:

	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> HUDClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> WinScreenClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> LoseScreenClass;

	UPROPERTY()
		UUserWidget* HUD;

	UPROPERTY(EditAnywhere)
		float RestartDelay = 5;

	FTimerHandle RestartTimer;
};
