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

	SpawnEnemies();
	
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

void AWaveSpawner::SpawnEnemies()
{
	//Spawn enemies at wave spawner location
 	ATankAI* Enemy = GetWorld()->SpawnActor<ATankAI>(EnemyClass, GetActorLocation(), GetActorRotation());

	Enemy->SetOwner(this);

	EnemyArr.Add(Enemy);
}

void AWaveSpawner::AllEnemiesDead()
{
	bWaveComplete = false;
	
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

