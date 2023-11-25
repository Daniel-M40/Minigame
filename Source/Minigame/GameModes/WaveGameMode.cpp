// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Minigame/Controllers/AI/TankAIController.h"
#include "Minigame/Controllers/Player/TankController.h"
#include "Minigame/Pawns/Tank/Tank.h"
#include "Minigame/PowerUps/PowerUp.h"
#include "Minigame/WaveSpawner/WaveSpawner.h"

AWaveGameMode::AWaveGameMode()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultPawnClass = ATank::StaticClass();

}


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

void AWaveGameMode::EndGame()
{
	//Game is over, flag to show the GameOver Widget
	bGameOver = true;

	//Game over text
	EndGameTxt = "Game Over!!";	
	
}

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
