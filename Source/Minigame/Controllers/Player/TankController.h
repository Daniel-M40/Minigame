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

private:
	
	FTimerHandle PossesTimerHandle;

public:
	bool bHasSpawnedTank = false;

	bool bIsSpawningTank = false;
	
#pragma endregion 


#pragma region Actions
	
	virtual void BeginPlay() override;

	void PossesPawn(float duration);

	virtual void OnPossess(APawn* InPawn) override;
	
#pragma endregion 

};
