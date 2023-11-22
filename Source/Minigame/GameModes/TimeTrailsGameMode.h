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
	FTimerHandle TimerHandle;

	UPROPERTY(EditAnywhere, Category="Config", meta=(DisplayName="Turret Class"))
	TSubclassOf<class ATurret> TurretClass;

	UPROPERTY(EditAnywhere, Category="Config", meta=(DisplayName="Default Pawn Class"))
	TSubclassOf<APawn> PawnClass;
	
	int TurretAmount = 0;

public:
	UPROPERTY(BlueprintReadOnly, Category="Time")
	float Timer = 0.f;
	
	UPROPERTY(EditAnywhere, Category="Time")
	float TimerRate = 0.1f;
	
	UPROPERTY(EditAnywhere, Category="Show Cursor")
	bool bShowCursor = false;

	UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "Game Over"))
	bool bGameOver;

	UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "End Game Text"))
	FString EndGameTxt;

	UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "Timer String"))
	FString TimerText;
	
	#pragma endregion

	#pragma region Actions

public:
	void BeginPlay() override;
	
	void GetTimer();

	void StopTimer();

	void DecreaseTurretAmount();

	void EndGame(bool bPlayerWon);
	
	#pragma endregion
	
};
