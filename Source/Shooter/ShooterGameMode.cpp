// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "Shooter/Character/AIControl.h"

void AShooterGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	// Debug code
	//UE_LOG(LogTemp, Warning, TEXT("A character was killed"))

	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController != nullptr)
	{
		EndGame(false);
	}

	// Loop for finding all the AI in the world
	for (AAIControl* Controller : TActorRange<AAIControl>(GetWorld()))
	{
		if (!Controller->AIIsDead())
		{
			return;
		}
	}

	EndGame(true);
}

void AShooterGameMode::EndGame(bool bIsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}
