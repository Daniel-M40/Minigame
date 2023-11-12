// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeTrailsGameMode.h"

void ATimeTrailsGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(
		TimerHandle, this, &ATimeTrailsGameMode::IncreaseTimer, 1.f, true, 0.0);
}

void ATimeTrailsGameMode::IncreaseTimer()
{
	Timer++;
}
