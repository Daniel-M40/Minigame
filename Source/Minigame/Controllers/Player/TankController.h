// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankController.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAME_API ATankController : public APlayerController
{
	GENERATED_BODY()

#pragma region Properties

#pragma region Properties
	
private:

	//Player HUD Widget class
	UPROPERTY(EditAnywhere, Category="UI")
	TSubclassOf<class UUserWidget> PlayerHUDClass;

	//Contains created HUD Widget
	UPROPERTY(EditAnywhere, Category="UI")
	UUserWidget* PlayerHUD;
	

public:
	//Flag to check if the tank is spawned when swapping between super <--> original
	bool bHasSpawnedTank = false;

	//Flag to show if we are in the process of spawning the tank
	bool bIsSpawningTank = false;

#pragma endregion
	
#pragma endregion 


#pragma region Actions
	
	virtual void BeginPlay() override;

	//Removes HUD from viewport
	void RemoveHUD();

	//Adds HUD to viewport
	void ShowHUD();

	
#pragma endregion 

};
