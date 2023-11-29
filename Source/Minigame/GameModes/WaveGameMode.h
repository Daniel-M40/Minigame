// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WaveGameMode.generated.h"

class ATankController;
class AWaveSpawner;

UCLASS()
class MINIGAME_API AWaveGameMode : public AGameModeBase
{
	GENERATED_BODY()

#pragma region Properties

private:
	//Class of wave spawner BP
	UPROPERTY(EditAnywhere, Category="Config")
	TSubclassOf<AWaveSpawner> WaveSpawnerClass;

	//Flag to show cursor or not
	UPROPERTY(EditAnywhere, Category="Config")
	bool bShowCursor = false;

	//Amount of wave spawners in the level
	UPROPERTY(VisibleAnywhere, Category="Config")
	int WaveSpawnerAmount;

	//Delay getting all the wave spawners at the start of the game
	FTimerHandle GetAllWavesTimer;

	//Timer to set how long the player possess the super tank
	FTimerHandle PossesTimerHandle;

	//Rate for delaying get all the wave spawners in the level
	float GetAllWavesDelay = 2.5f;
	
	//Array of wave spawner actors in the level
	TArray<AWaveSpawner*> WaveSpawnerArr;

	//Flag to show whether all waves are complete
	bool bAllWavesComplete = true;

	//Length of power up array
	int PowerUpArrLength = 0;

	//Rate to determine how often we spawn a power up
	int PowerUpSpawnRate = 1;
	
	//Array of power up classes
	UPROPERTY(EditAnywhere, Category="Power Ups")
	TArray<TSubclassOf<class APowerUp>> PowerUpArr;
	
	class ATankAIController* AIController;

	// Add this property to specify the default player controller class
	UPROPERTY(EditDefaultsOnly, Category = "Player Controller")
	TSubclassOf<ATankController> DefaultPlayerControllerClass;

	//Reference to orginal tank
	class ATank* OriginalTank;

	//Class of tank bp
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ATank> TankClass;

	//reference to super tank
	class ASuperTank* SuperTank;
	
public:
	//Shows the current wave
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Wave Config")
	int CurrentWave = 0;
	
	//Contains the players score when they destroy an enemy
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Config")
	int PlayerScore = 0;

	//Flag to show whether the game is over
	UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "Game Over"))
	bool bGameOver;

	//Text to display when the game is over
	UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "End Game Text"))
	FString EndGameTxt;

	//Text to show what wave it is currently
	UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "Current Wave Text"))
	FString CurrentWaveTxt;

	ATankController* PlayerController;

public:
	//Flag to show whether the player is a super tank or not
	bool bIsSuperTank = false;
	
#pragma endregion

#pragma region Actions
public:
	void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

private:
	//Get all wave spawners in the level
	void GetAllWaveSpawner();
	
	//Check if wave is finished if all wave spawners are "complete"
	void AllWavesComplete();
	
public:
	AWaveGameMode();
	
	//Function that ends the game
	void EndGame();

	//Increments the players overall score from killing enemies
	void IncreaseScore();

	//Randomly spawn power up at location
	void SpawnPowerUp(const FVector Location, const FRotator Rotation);

	//Spawn super tank for a certain duration
	void SpawnSuperTank(class ATank* Tank, TSubclassOf<class ASuperTank> SuperTankClass, float duration);

	//Repossess original tank
	void PossesOriginalTank();

	
#pragma endregion
};
