// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "Minigame/WaveSpawner/WaveSpawner.h"

AWaveGameMode::AWaveGameMode()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AWaveGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	GetAllWaveSpawner();

	//Hide Mouse Cursor
	UGameplayStatics::GetPlayerController(this, 0)->SetShowMouseCursor(bShowCursor);
	
}

void AWaveGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

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

		for (AWaveSpawner* WaveSpawner : WaveSpawnerArr)
		{
			WaveSpawner->StartWave();
		}

		bAllWavesComplete = false;
	}
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
}


