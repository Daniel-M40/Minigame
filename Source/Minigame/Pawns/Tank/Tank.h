// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Minigame/Pawns/BasePawn.h"
#include "Tank.generated.h"

UCLASS()
class MINIGAME_API ATank : public ABasePawn
{
	GENERATED_BODY()

	#pragma region Properties

private:
	
	//Camera Config
	UPROPERTY(EditAnywhere, Category="Camera Config")
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category="Camera Config")
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere, Category="Camera Config")
	bool CameraLag = true;

	UPROPERTY(EditAnywhere, Category="Camera Config")
	bool CameraRotationLag = true;
	

	//Custom Movement Component
	UPROPERTY(EditAnywhere, Category="Movement Config")
	class UPlayerMovementComponent* PlayerMovementComponent;

	

	//Player Controller
	class APlayerController* PlayerController;

	//Shooting delay for tank
	bool bCanShoot;

	UPROPERTY(EditAnywhere, Category="Combat")
	float FireRate = 1.f;


	bool bHasFasterMovement = false;

	float MovementSpeedMultiplier = 2.f;

	//Timer to delay the players firing by
	FTimerHandle ShootTimeHandle;
	
	//Timer to increase the players speed for
	FTimerHandle SpeedTimerHandle;
	
	//Debug Mode
	UPROPERTY(EditAnywhere, Category="Debugging", meta=(DisplayName="Show Debug Spheres"))
	bool bIsDebugMode = false;

public:
	bool bIsAlive = true;

	#pragma  endregion
	
	#pragma region Actions
	
public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveHandler(const struct FInputActionValue& Value);
	
	void TurnHandler(const struct FInputActionValue& Value);

	void ShootHandler(const struct FInputActionValue& Value);

	void EnableShooting();
	
	//Increases the players health by a certain value
	void IncreaseHealth(float healthValue);

	//Function that creates a timer that increases the players speed by
	void EnableFasterMovement(float multiplier, float time);

	void DisableFasterMovement();
	
	#pragma endregion

	virtual void HandleDestruction() override;

};
