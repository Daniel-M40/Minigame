﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Minigame/Pawns/BasePawn.h"
#include "Turret.generated.h"

UCLASS()
class MINIGAME_API ATurret : public ABasePawn
{
	GENERATED_BODY()

#pragma region Properties

private:

	//Timer handle for setting a delay on when the turret can shoot
	FTimerHandle TimerHandle;


protected:
	class ATank* Tank;
	
	UPROPERTY(EditAnywhere, Category = "Tower Config")
	float FireRate = 2.f;

	UPROPERTY(EditAnywhere, Category = "Tower Config", meta = (DisplayName = "Turret Range"))
	float FireRange = 10.f;
#pragma endregion
	
	
public:
	// Sets default values for this pawn's properties
	ATurret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void HandleDestruction() override;

	//Check if the actor can fire
	void CheckFireCondition();

	//Is actor in range of turret
	bool IsActorInRange(const FVector& ActorLocation);

	void ResetTimer();
};
