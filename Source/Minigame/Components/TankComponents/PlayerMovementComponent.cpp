// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMovementComponent.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Minigame/Pawns/Tank/Tank.h"

// Sets default values for this component's properties
UPlayerMovementComponent::UPlayerMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<ATank>(GetOwner());
	
	//Get Player controller
	PlayerController = Cast<APlayerController>(Player->GetController());
	
}


// Called every frame
void UPlayerMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UPlayerMovementComponent::BindInputActions(UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	
	if (EIC)
	{
		EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &UPlayerMovementComponent::MoveHandler);
		EIC->BindAction(TurnAction, ETriggerEvent::Triggered, this, &UPlayerMovementComponent::TurnHandler);
		EIC->BindAction(ShootAction, ETriggerEvent::Triggered, this, &UPlayerMovementComponent::ShootHandler);
	}
}

void UPlayerMovementComponent::MoveHandler(const FInputActionValue& Value)
{
	//If we have picked up the speed power up multiply the movement speed by a value
	if (bHasFasterMovement)
	{
		Player->AddMovementInput(Player->GetActorForwardVector() * Value.Get<float>() * GetWorld()->DeltaTimeSeconds *
			MovementSpeed * MovementSpeedMultiplier);
	}
	else
	{
		Player->AddMovementInput(Player->GetActorForwardVector() * Value.Get<float>() * GetWorld()->DeltaTimeSeconds,
						MovementSpeed);
	}
}

void UPlayerMovementComponent::TurnHandler(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("TurnHandler Called"));
	Player->AddControllerYawInput(Value.Get<float>() * GetWorld()->DeltaTimeSeconds * RotationSpeed);
}

void UPlayerMovementComponent::ShootHandler(const FInputActionValue& Value)
{
	if (bCanShoot)
	{
		Player->Shoot();
		bCanShoot = false;
	}
}
