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

	UPROPERTY(EditAnywhere, Category="", meta=(DisplayName=""))
	TSubclassOf<AActor> TurretClass;

	int TurretAmount = 0;

public:
	UPROPERTY(BlueprintReadOnly, Category="Time")
	float Timer = 0.f;

	
	#pragma endregion

	#pragma region Actions

	void BeginPlay() override;
	
	void IncreaseTimer();

	void StopTimer();

	void DecreaseTurretAmount();
	
	#pragma endregion
	
};
