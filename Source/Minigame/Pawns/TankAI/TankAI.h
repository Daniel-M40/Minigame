// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Minigame/Pawns/Turret/Turret.h"
#include "TankAI.generated.h"

UCLASS()
class MINIGAME_API ATankAI : public ATurret
{
	GENERATED_BODY()

#pragma region Properties
	
public:
	//Movement speed of enemy
	UPROPERTY(EditAnywhere, Category="Movement")
	float MovementSpeed = 0.1f;

	//Range in which the actor stays away from the tank by
	UPROPERTY(EditAnywhere, Category="Movement")
	float Range = 500.f;

	class AAIController* AIController;
	
#pragma endregion

#pragma region Actions

private:
	void MoveTankAI();
	
public:
	// Sets default values for this pawn's properties
	ATankAI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void IncreaseStats(const float SpeedIncrement, const float FireRateDecrease);

	virtual void HandleDestruction() override;
	
#pragma endregion
};
