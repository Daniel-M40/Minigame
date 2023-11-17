// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeTrailsGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Minigame/Pawns/Turret/Turret.h"

void ATimeTrailsGameMode::BeginPlay()
{
	Super::BeginPlay();

	//Set timer 
	GetWorldTimerManager().SetTimer(
		TimerHandle, this, &ATimeTrailsGameMode::IncreaseTimer, 1.f, true, 0.0);

	TArray<AActor*> TurretArr; //Array of turret actors in the level
	TurretClass = ATurret::StaticClass();

	//Get all actors of class ATurret
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), TurretClass, TurretArr);

	//Store the amount of turrets
	TurretAmount = TurretArr.Num();

	//Hide Mouse Cursor
	UGameplayStatics::GetPlayerController(this, 0)->SetShowMouseCursor(bShowCursor);
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

	if (TurretAmount <= 0)
	{
		//Player has destroyed all turrets
		//Stop the timer
		StopTimer();
	}
}
