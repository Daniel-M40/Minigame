﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveSpawner.h"
#include "Minigame/Pawns/TankAI/BaseAI.h"


// Sets default values
AWaveSpawner::AWaveSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWaveSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	StartWave();
}

// Called every frame
void AWaveSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Check if the wave is not complete then check if all the enemies are complete
	if (!bWaveComplete)
	{
		//Check if all enemies are dead
		AreAllEnemiesDead();
	}
}

void AWaveSpawner::StartWave()
{
	//Set current enemy amount to 0
	CurrentEnemyAmount = 0;

	bWaveComplete = false;

	//Set flag to true as we are spawning enemies
	bSpawningEnemies = true;

	//Clear enemy array
	EnemyArr.Empty();
	
	//Set timer to spawn enemy
	GetWorldTimerManager().SetTimer(
		SpawnerTimeHandle, this, &AWaveSpawner::SpawnEnemy, SpawnRate, false);
}

void AWaveSpawner::SpawnEnemy()
{
	//Spawn enemies at wave spawner location
 	ABaseAI* Enemy = GetWorld()->SpawnActor<ABaseAI>(EnemyClass, GetActorLocation(), GetActorRotation());
	
	//Increase enemies stats
	IncreaseStats();
	Enemy->IncreaseStats(MovementSpeed, FireRate);

	Enemy->ResetTimer();
	
	Enemy->SetOwner(this);
	
	//Add enemy to array to keep track of all enemies spawned
	EnemyArr.Add(Enemy);

	//Increment counter to show how many enemies have been spawned
	CurrentEnemyAmount++;

	//Check if we need to still spawn enemies
	if (CurrentEnemyAmount < SpawnAmount)
	{
		//Set timer to spawn enemy
		GetWorldTimerManager().SetTimer(
			SpawnerTimeHandle, this, &AWaveSpawner::SpawnEnemy, SpawnRate, false);
	}
	else
	{
		bSpawningEnemies = false;
	}
}

void AWaveSpawner::AreAllEnemiesDead()
{
	bWaveComplete = false;

	//If we are spawning enemies do not check if all enemies are dead
	if (bSpawningEnemies)
	{
		return;
	}
	
	//Loop though tank AI arr
	for (ABaseAI* TankAI : EnemyArr)
	{
		//Check if tank is valid
		//Break out of loop if any tanks are alive
		if (IsValid(TankAI))
		{
			break;
		}

		//Otherwise all tanks are dead so wave is completed
		bWaveComplete = true;
	}
}

void AWaveSpawner::IncreaseStats()
{
	MovementSpeed += MovementSpeedIncrease;
	FireRate -= FireRateDecrease;
}

