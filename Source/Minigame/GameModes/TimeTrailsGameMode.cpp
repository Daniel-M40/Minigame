// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeTrailsGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetStringLibrary.h"
#include "Minigame/Pawns/Tank/Tank.h"
#include "Minigame/Pawns/Turret/Turret.h"


/**
 * Start timers and spawn in turrets
 */
void ATimeTrailsGameMode::BeginPlay()
{
	Super::BeginPlay();

	//Set delay on spawning turrets
	//Randomly Spawn Turrets in level
	GetWorldTimerManager().SetTimer(SpawnTurretsHandle,
		this, &ATimeTrailsGameMode::CreateTurrets, .5f, false, 0.0);

	//Set global timer for how long the player takes to complete the level 
	GetWorldTimerManager().SetTimer(
		PlayerTimerHandle, this, &ATimeTrailsGameMode::GetTimer, TimerRate, true, 0.0);
	

	//Hide Mouse Cursor
	UGameplayStatics::GetPlayerController(this, 0)->SetShowMouseCursor(bShowCursor);

}


/**
 * Get timer and set it in timer text to be displayed in the UI
 */
void ATimeTrailsGameMode::GetTimer()
{
	double Timer;

	//Get current game time in seconds, also effected when game is paused and slo-mo
	Timer = UKismetSystemLibrary::GetGameTimeInSeconds(this);

	//Convert the time in seconds to string to display
	TimerText = UKismetStringLibrary::TimeSecondsToString(Timer);
}


/**
 * Stop the timer when the player finishes the level or dies
 */
void ATimeTrailsGameMode::StopTimer()
{
	GetWorldTimerManager().ClearTimer(PlayerTimerHandle);
}


/**
 * Decrease turret count so we know when we have destroyed all turrets
 */
void ATimeTrailsGameMode::DecreaseTurretAmount()
{
	TurretAmount--;

	if (TurretAmount <= 0)
	{
		//Player has destroyed all turrets end the game
		EndGame(true);
	}
}


/**
 * Ends the game and shows end game text
 * @param bPlayerWon Flag to show if the player has won
 */
void ATimeTrailsGameMode::EndGame(bool bPlayerWon)
{
	//Game is over stop the timer
	StopTimer();

	//Game is over , flag to show the GameOver Widget
	bGameOver = true;

	//Show certain text depending if the player has won or not
	if (bPlayerWon)
	{
		EndGameTxt = "Game Won!!";
	}
	else
	{
		EndGameTxt = "Game Over!!";	
	}
	
}


/**
 * Spawn turrets in level randomly between width and height
 */
void ATimeTrailsGameMode::CreateTurrets()
{
	FActorSpawnParameters SpawnParams;

	// Forces the pawn to spawn even if colliding
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	for (int i = 0; i < TurretSpawnAmount; i++)
	{
		if (TurretClass)
		{
			const float randX = FMath::FRandRange(-SpawnWidth, SpawnWidth);
			const float randY = FMath::FRandRange(-SpawnHeight, SpawnHeight);
			
			FVector actorLocation = FVector(randX, randY, 10.f);
			
			ATurret* tempTurret = GetWorld()->SpawnActor<ATurret>(TurretClass, actorLocation, FRotator::ZeroRotator, SpawnParams);

			TurretArr.Add(tempTurret);
			
			TurretAmount++;
		}
	}
}
