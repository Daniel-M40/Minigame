// Fill out your copyright notice in the Description page of Project Settings.


#include "TankController.h"

void ATankController::BeginPlay()
{
	Super::BeginPlay();

	DefaultMouseCursor = EMouseCursor::Hand;
}
