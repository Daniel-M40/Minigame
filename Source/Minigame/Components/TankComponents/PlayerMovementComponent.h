// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerMovementComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MINIGAME_API UPlayerMovementComponent : public UActorComponent
{
	GENERATED_BODY()

#pragma region Properties
private:
	class ATank* Player;
	
	//Player Controller
	class APlayerController* PlayerController;

public:
	//Shooting delay for tank
	bool bCanShoot = true;

	bool bHasFasterMovement = false;

	float MovementSpeedMultiplier = 2.f;

	//Movement Config
	UPROPERTY(EditAnywhere, Category="Movement Config", meta=(DisplayName="Movement Speed"))
	float MovementSpeed = 100.f;

	UPROPERTY(EditAnywhere, Category="Movement Config", meta=(DisplayName="Rotation Speed"))
	float RotationSpeed = 100.f;

	

	//Input Config - Input actions and mapping context
	UPROPERTY(EditAnywhere)
	class UInputMappingContext* MappingContext;
	
	UPROPERTY(EditAnywhere)
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere)
	UInputAction* ShootAction;

	UPROPERTY(EditAnywhere)
	UInputAction* TurnAction;
	
#pragma endregion

#pragma region Actions
	
public:
	// Sets default values for this component's properties
	UPlayerMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;


	void BindInputActions(class UInputComponent* PlayerInputComponent);

	void MoveHandler(const struct FInputActionValue& Value);
	
	void TurnHandler(const struct FInputActionValue& Value);

	void ShootHandler(const struct FInputActionValue& Value);

	void EnableShooting();

	
#pragma endregion
};
