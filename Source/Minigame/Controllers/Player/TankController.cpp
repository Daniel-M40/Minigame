// Fill out your copyright notice in the Description page of Project Settings.


#include "TankController.h"

#include "Blueprint/UserWidget.h"

void ATankController::BeginPlay()
{
	Super::BeginPlay();

	DefaultMouseCursor = EMouseCursor::Hand;

	//Create HUD widget for viewport
	if (PlayerHUDClass)
	{
		PlayerHUD = CreateWidget(this, PlayerHUDClass);

		ShowHUD();
	}
}

void ATankController::RemoveHUD()
{
	PlayerHUD->RemoveFromViewport();
}

void ATankController::ShowHUD()
{
	if (PlayerHUD)
	{
		PlayerHUD->AddToViewport();
	}
}


void ATankController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	
}
