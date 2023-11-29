// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TimeTrailsGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAME_API ATimeTrailsGameMode : public AGameModeBase
{
	GENERATED_BODY()

	#pragma region Properties
	
private:
	//Tracks how long the player takes to finish the level
	FTimerHandle PlayerTimerHandle;

	//Delay before spawning random turrets
	FTimerHandle SpawnTurretsHandle;

	//How many turrets we spawn in the level
	UPROPERTY(EditAnywhere, Category="Spawn Config")
	int TurretSpawnAmount = 4;

	//Width of range in which we want to spawn the turrets
	UPROPERTY(EditAnywhere, Category="Spawn Config")
	float SpawnWidth = 500.f;
	
	//Height of range in which we want to spawn the turrets
	UPROPERTY(EditAnywhere, Category="Spawn Config")
	float SpawnHeight = 500.f;

	//Class of turret we want to spawn
	UPROPERTY(EditAnywhere, Category="Config", meta=(DisplayName="Turret Class"))
	TSubclassOf<class ATurret> TurretClass;

	//Array of turrets we have spawned
	TArray<class ATurret*> TurretArr;
		
	int TurretAmount = 0;

	class ATankController* PlayerController;

public:
	//Rate of when we call athe get timer function
	UPROPERTY(EditAnywhere, Category="Time")
	float TimerRate = 0.1f;

	//Flag to show cursor or not
	UPROPERTY(EditAnywhere, Category="Show Cursor")
	bool bShowCursor = false;

	//Flag to show if the game is finished
	UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "Game Over"))
	bool bGameOver;

	//Text to show when the game is over
	UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "End Game Text"))
	FString EndGameTxt;

	//Text to show the time passed
	UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "Timer String"))
	FString TimerText;
	
	#pragma endregion

	#pragma region Actions

public:
	void BeginPlay() override;

	//Get the current time passed 
	void GetTimer();

	//Stop the timer set
	void StopTimer();
	
	//When turret is destroyed decrease turret amount
	void DecreaseTurretAmount();

	
	/**
	 * Ends the game
	 * @param bPlayerWon shows whether the player has won or lost
	 */
	void EndGame(bool bPlayerWon);


private:
	//Randomly spawns the turrets in the level
	void CreateTurrets();
	
	#pragma endregion
	
};
