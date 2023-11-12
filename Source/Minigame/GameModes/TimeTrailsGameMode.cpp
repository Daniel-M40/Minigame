// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeTrailsGameMode.h"

#include "Kismet/GameplayStatics.h"

class ATurret;

void ATimeTrailsGameMode::BeginPlay()
{
	Super::BeginPlay();

	//Set timer 
	GetWorldTimerManager().SetTimer(
		TimerHandle, this, &ATimeTrailsGameMode::IncreaseTimer, 1.f, true, 0.0);

	TArray<AActor*> TurretArr;

	//Get all actors of class ATurret
	UGameplayStatics::GetAllActorsOfClass(this, TurretClass, TurretArr);

	TurretAmount = TurretArr.Num();
}

void ATimeTrailsGameMode::IncreaseTimer()
{
	Timer++;
}

void ATimeTrailsGameMode::StopTimer()
{
	GetWorldTimerManager().ClearTimer(TimerHandle);
}

void ATimeTrailsGameMode::DecreaseTurretAmount()
{
	TurretAmount--;

	if (TurretAmount == 0)
	{
		//Player has destroyed all turrets
		//Stop the timer
		StopTimer();
	}
}
