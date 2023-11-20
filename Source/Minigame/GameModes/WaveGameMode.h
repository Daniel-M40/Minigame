// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WaveGameMode.generated.h"

UCLASS()
class MINIGAME_API AWaveGameMode : public AGameModeBase
{
	GENERATED_BODY()

#pragma region Properties

public:
	//Shows the current wave
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Wave Config")
	int CurrentWave = 1;

	
#pragma endregion

#pragma region Actions

	void BeginPlay() override;

public:
	//Check if wave is finished if all wave spawners are "complete"
	void AllWavesComplete();

	//Function that ends the game
	void GameEnd();

	//Increments the players overall score from killing enemies
	void IncreaseScore();

	void NextWave();
	
#pragma endregion
};
