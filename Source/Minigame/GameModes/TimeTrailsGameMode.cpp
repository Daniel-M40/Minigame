// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeTrailsGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetStringLibrary.h"
#include "Minigame/Pawns/Tank/Tank.h"
#include "Minigame/Pawns/Turret/Turret.h"

void ATimeTrailsGameMode::BeginPlay()
{
	Super::BeginPlay();

	//Set delay on spawning turrets
	//Randomly Spawn Turrets in level
	GetWorldTimerManager().SetTimer(SpawnTurretsHandle,
		this, &ATimeTrailsGameMode::CreateTurrets, .5f, false, 0.0);

	//Set timer 
	GetWorldTimerManager().SetTimer(
		PlayerTimerHandle, this, &ATimeTrailsGameMode::GetTimer, TimerRate, true, 0.0);
	

	//Hide Mouse Cursor
	UGameplayStatics::GetPlayerController(this, 0)->SetShowMouseCursor(bShowCursor);

}

void ATimeTrailsGameMode::GetTimer()
{
	double Timer;

	//Get current game time in seconds, also effected when game is paused and slo-mo
	Timer = UKismetSystemLibrary::GetGameTimeInSeconds(this);

	//Convert the time in seconds to string to display
	TimerText = UKismetStringLibrary::TimeSecondsToString(Timer);
}

void ATimeTrailsGameMode::StopTimer()
{
	GetWorldTimerManager().ClearTimer(PlayerTimerHandle);
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
