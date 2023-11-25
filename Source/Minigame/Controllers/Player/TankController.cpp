// Fill out your copyright notice in the Description page of Project Settings.


#include "TankController.h"

void ATankController::BeginPlay()
{
	Super::BeginPlay();

	DefaultMouseCursor = EMouseCursor::Hand;
}

void ATankController::PossesPawn(float duration)
{
	
}

void ATankController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	
}
