// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveSpawner.h"

#include "Minigame/Pawns/TankAI/TankAI.h"


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

	if (!bWaveComplete)
	{
		AllEnemiesDead();
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
 	ATankAI* Enemy = GetWorld()->SpawnActor<ATankAI>(EnemyClass, GetActorLocation(), GetActorRotation());
	
	//Increase enemies stats
	IncreaseStats();
	Enemy->IncreaseStats(Health, MovementSpeed, FireRate);

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

void AWaveSpawner::AllEnemiesDead()
{
	bWaveComplete = false;

	//If we are spawning enemies do not check if all enemies are dead
	if (bSpawningEnemies)
	{
		return;
	}
	
	//Loop though tank AI arr
	for (ATankAI* TankAI : EnemyArr)
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
	Health += HealthIncrease;
	MovementSpeed += MovementSpeedIncrease;
	FireRate -= FireRateDecrease;
}

