// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaveSpawner.generated.h"

UCLASS()
class MINIGAME_API AWaveSpawner : public AActor
{
	GENERATED_BODY()

#pragma region Properties
private:
	//Value that determines the spawn rate of the enemies 
	UPROPERTY(EditAnywhere, Category="Wave Config")
	float SpawnRate = 1.f;

	FTimerHandle SpawnerTimeHandle;
	
	//Value that shows how many enemies will spawn at the start
	UPROPERTY(EditAnywhere, Category="Wave Config")
	int SpawnAmount = 1;

	//Value that shows how many enemies are currently spawning
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Wave Config", meta=(AllowPrivateAccess=true))
	int CurrentEnemyAmount = 0;
	
	//Value that increments the enemies status as the waves progress
	UPROPERTY(EditAnywhere, Category="Enemy")
	float MovementSpeedIncrease = .01f;

	UPROPERTY(EditAnywhere, Category="Enemy")
	float HealthIncrease = 2.5f;

	UPROPERTY(EditAnywhere, Category="Enemy")
	float FireRateDecrease = .1f;

	//Enemy Movement speed
	UPROPERTY(VisibleAnywhere, Category="Enemy")
	float MovementSpeed = .25f;

	//Enemy health
	UPROPERTY(VisibleAnywhere, Category="Enemy")
	float Health = 0.f;

	//Fire rate
	UPROPERTY(VisibleAnywhere, Category="Enemy")
	float FireRate = 3.f;
	
	//Increment the decreases the time enemies will take to shoot at the player
	UPROPERTY(EditAnywhere, Category="Enemy")
	float ShootingDelay = .25f;
	
	UPROPERTY(EditAnywhere, Category = "Enemy")
	TSubclassOf<class ABaseAI> EnemyClass;

	//Stores enemies that have been spawned
	TArray<class ABaseAI*> EnemyArr;

public:
	
	//Flag that shows whether all the enemies have died and the wave is completed
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Wave Config")
	bool bWaveComplete;

	bool bSpawningEnemies = false;
	
#pragma endregion

#pragma region Actions
	
public:
	// Sets default values for this actor's properties
	AWaveSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void StartWave();

	
private:
		
	//Spawn enemy at spawn point
	void SpawnEnemy();

	//Check if all the enemies are dead
	void AreAllEnemiesDead();

	void IncreaseStats();
	
#pragma endregion
};
