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

	//Camera Config
	UPROPERTY(EditAnywhere, Category="Camera Config")
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category="Camera Config")
	class USpringArmComponent* SpringArmComponent;
	
	//Movement Config
	UPROPERTY(EditAnywhere, Category="Movement Config", meta=(DisplayName="Tank Movement Speed"))
	float MovementSpeed = 100.f;

	UPROPERTY(EditAnywhere, Category="Movement Config", meta=(DisplayName="Tank Rotation Speed"))
	float RotationSpeed = 100.f;
	

	//Input Config - Input actions and mapping context
	UPROPERTY(EditAnywhere)
	class UInputMappingContext* TankMappingContext;

	UPROPERTY(EditAnywhere)
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere)
	UInputAction* ShootAction;

	UPROPERTY(EditAnywhere)
	UInputAction* TurnAction;

	//Player Controller
	class APlayerController* PlayerController;
	
	
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
	
	#pragma endregion

	virtual void HandleDestruction() override;

};
