﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "Minigame/Controllers/AI/TankAIController.h"
#include "Minigame/Controllers/Player/TankController.h"
#include "Minigame/Pawns/SuperTank/SuperTank.h"
#include "Minigame/Pawns/Tank/Tank.h"
#include "Minigame/PowerUps/PowerUp.h"
#include "Minigame/WaveSpawner/WaveSpawner.h"

AWaveGameMode::AWaveGameMode()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultPawnClass = ATank::StaticClass();

}


/**
 * Gets all waves and power ups lengths
 */
void AWaveGameMode::BeginPlay()
{
	Super::BeginPlay();

	//Add getting all wave spawners on a delay
	GetWorldTimerManager().SetTimer(GetAllWavesTimer, this,
		&AWaveGameMode::GetAllWaveSpawner, GetAllWavesDelay, false);
	

	//Get length of power up array
	PowerUpArrLength = PowerUpArr.Num();
}

void AWaveGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AllWavesComplete();
}


/**
 * Checks to see if all waves have completed, if so start new wave
 */
void AWaveGameMode::AllWavesComplete()
{
	// Check if all wave spawners are complete
	for (int i = 0; i < WaveSpawnerAmount; i++)
	{
		if (WaveSpawnerArr[i] && !WaveSpawnerArr[i]->bWaveComplete)
		{
			bAllWavesComplete = false; // If any wave spawner is incomplete, set the flag to false
			break; // No need to continue checking, we already know not all waves are complete
		}

		//Otherwise all waves are complete and set flag to true
		bAllWavesComplete = true;
	}

	//If all waves complete spawn enemies again
	if (bAllWavesComplete)
	{
		CurrentWave++;
		CurrentWaveTxt = "Wave: " + FString::FromInt(CurrentWave);

		for (AWaveSpawner* WaveSpawner : WaveSpawnerArr)
		{
			WaveSpawner->StartWave();
		}

		bAllWavesComplete = false;
	}
}


/**
 * Gets all instances of the wave spawner and stores them
 */
void AWaveGameMode::GetAllWaveSpawner()
{
	TArray<AActor*> tempWaveSpawnerArr;
	WaveSpawnerClass = AWaveSpawner::StaticClass();

	//Get all actors of class of AWaveSpawner
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), WaveSpawnerClass, tempWaveSpawnerArr);


	for (AActor* Actor : tempWaveSpawnerArr)
	{
		if (Actor)
		{
			//Cast actors to wave spawner and add to array
			WaveSpawnerArr.Add(Cast<AWaveSpawner>(Actor));
		}
	}
	
	//Store the amount of wave spawners in the world
	WaveSpawnerAmount = WaveSpawnerArr.Num();

	UE_LOG(LogTemp, Warning, TEXT("Num of waves spawner: %d"), WaveSpawnerAmount);
}


/**
 * Function that will end the game and display text for the game over screen
 */
void AWaveGameMode::EndGame()
{
	//Game is over, flag to show the GameOver Widget
	bGameOver = true;

	//Game over text
	EndGameTxt = "Game Over!!";


	//Remove HUD when game is over
	PlayerController->RemoveHUD();
	
}


/**
 * Increase player score
 */
void AWaveGameMode::IncreaseScore()
{
	PlayerScore++;
}

void AWaveGameMode::SpawnPowerUp(const FVector Location, const FRotator Rotation)
{
	//Randomly spawn power up if the value is 1
	const int spawnPowerUp = FMath::RandRange(0, PowerUpSpawnRate);

	if (spawnPowerUp)
	{
		//Randomly pick power up in array
		const int index = FMath::RandRange(0, PowerUpArrLength - 1);
		
		//Spawn power up in location
		if (PowerUpArr[index])
		{
			GetWorld()->SpawnActor<APowerUp>(PowerUpArr[index], Location, Rotation);
		}
		
	}
}

/**
 * Function that will spawn and possess super tank for a duration
 * @param Tank Reference to current tank player is possessing
 * @param SuperTankClass Class of the super tank
 * @param duration How long the player will possess the tank for
 */
void AWaveGameMode::SpawnSuperTank(ATank* Tank, TSubclassOf<ASuperTank> SuperTankClass, float duration)
{
	//Assign tank to orignal tank
	OriginalTank = Tank;

	//Set flag to show that we are spawning super tank
	bIsSuperTank = true;
	
	if (OriginalTank)
	{
		//Get player controller
		PlayerController = Cast<ATankController>(UGameplayStatics::GetPlayerController(this, 0));
	}

	if (PlayerController && SuperTankClass)
	{
		FActorSpawnParameters SpawnParams;

		// Forces the pawn to spawn even if colliding
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		FVector NewLocation = OriginalTank->GetActorLocation();
		FRotator NewRotation = OriginalTank->GetActorRotation();

		
		//Spawn new pawn
		SuperTank = GetWorld()->SpawnActor<ASuperTank>(SuperTankClass, NewLocation, NewRotation, SpawnParams);
		
		if (SuperTank)
		{
			//Posses super tank
			PlayerController->UnPossess();
			PlayerController->Possess(SuperTank);
			SuperTank->EnableInput(PlayerController);

			//Set health to what the player currently had
			SuperTank->SetHealth(OriginalTank->GetHealth());
			
			OriginalTank->Destroy();
			
			//Set timer for how long we posses the tank for
			GetWorldTimerManager().SetTimer(PossesTimerHandle, this, &AWaveGameMode::PossesOriginalTank, duration, false);
		}
			
	}
	
}


/**
 * Spawns the original tank pawn at the location and rotation of the super tank
 * Then destroys the super tank
 */
void AWaveGameMode::PossesOriginalTank()
{
	if (TankClass)
	{
		FActorSpawnParameters SpawnParams;

		// Forces the pawn to spawn even if colliding
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		
		//Get Old pawn location and rotation
		FVector NewLocation = SuperTank->GetActorLocation();
		FRotator NewRotation = SuperTank->GetActorRotation();
		
		
		//Spawn new pawn
		OriginalTank = GetWorld()->SpawnActor<ATank>(TankClass, NewLocation, NewRotation, SpawnParams);
		

		//Possess new pawn
		PlayerController->UnPossess();
		PlayerController->Possess(OriginalTank);
 		OriginalTank->EnableInput(PlayerController);

		bIsSuperTank = false;
		

		//Set health to what the player currently had
		OriginalTank->SetHealth(SuperTank->GetHealth());
		
		//Destroy super tank
		SuperTank->Destroy();
		
	}
}
