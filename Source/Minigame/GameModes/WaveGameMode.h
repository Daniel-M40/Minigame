﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WaveGameMode.generated.h"

class AWaveSpawner;

UCLASS()
class MINIGAME_API AWaveGameMode : public AGameModeBase
{
	GENERATED_BODY()

#pragma region Properties

private:
	UPROPERTY(EditAnywhere, Category="Config")
	TSubclassOf<AWaveSpawner> WaveSpawnerClass;

	UPROPERTY(EditAnywhere, Category="Config")
	bool bShowCursor = false;
	
	UPROPERTY(VisibleAnywhere, Category="Config")
	int WaveSpawnerAmount;

	FTimerHandle GetAllWavesTimer;

	float GetAllWavesDelay = 2.5f;
	
	//Array of wave spawner actors in the level
	TArray<AWaveSpawner*> WaveSpawnerArr;
	
	bool bAllWavesComplete = true;
	
public:
	//Shows the current wave
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Wave Config")
	int CurrentWave = 1;

	//Contains the players score when they destroy an enemy
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Config")
	int PlayerScore = 0;

	UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "Game Over"))
	bool bGameOver;

	UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "End Game Text"))
	FString EndGameTxt;

	
#pragma endregion

#pragma region Actions
public:
	void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

private:
	void GetAllWaveSpawner();
	
	//Check if wave is finished if all wave spawners are "complete"
	void AllWavesComplete();
	
public:
	AWaveGameMode();
	
	//Function that ends the game
	void EndGame();

	//Increments the players overall score from killing enemies
	void IncreaseScore();

	
#pragma endregion
};
