// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeTrailsGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetStringLibrary.h"
#include "Minigame/Pawns/Tank/Tank.h"
#include "Minigame/Pawns/Turret/Turret.h"

void ATimeTrailsGameMode::BeginPlay()
{
	Super::BeginPlay();

	//Set timer 
	GetWorldTimerManager().SetTimer(
		TimerHandle, this, &ATimeTrailsGameMode::GetTimer, TimerRate, true, 0.0);

	TArray<AActor*> TurretArr; //Array of turret actors in the level
	TurretClass = ATurret::StaticClass();

	//Get all actors of class ATurret
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), TurretClass, TurretArr);

	//Store the amount of turrets
	TurretAmount = TurretArr.Num();

	//Hide Mouse Cursor
	UGameplayStatics::GetPlayerController(this, 0)->SetShowMouseCursor(bShowCursor);

	//Set default pawn class
	DefaultPawnClass = PawnClass;
}

void ATimeTrailsGameMode::GetTimer()
{
	//Get current game time in seconds, also effected when game is paused and slo-mo
	UKismetSystemLibrary::GetGameTimeInSeconds(this);

	//Convert the time in seconds to string to display
	TimerText = UKismetStringLibrary::TimeSecondsToString(UKismetSystemLibrary::GetGameTimeInSeconds(this));
}

void ATimeTrailsGameMode::StopTimer()
{
	GetWorldTimerManager().ClearTimer(TimerHandle);
}

void ATimeTrailsGameMode::DecreaseTurretAmount()
{
	TurretAmount--;

	if (TurretAmount <= 0)
	{
		//Player has destroyed all turrets end the game
		EndGame(true);
	}
}

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
