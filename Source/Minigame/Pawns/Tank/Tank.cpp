﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Minigame/GameModes/TimeTrailsGameMode.h"
#include "Minigame/GameModes/WaveGameMode.h"


// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComponent->SetupAttachment(BaseTowerMesh);
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	Camera->SetupAttachment(SpringArmComponent);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	//Spring arm config
	if (SpringArmComponent)
	{
		SpringArmComponent->bEnableCameraLag = CameraLag;
		SpringArmComponent->bEnableCameraRotationLag = CameraRotationLag;
	}
	
	//Get Player controller
	PlayerController = Cast<APlayerController>(GetController());

	//If we have player controller assign the mapping context to the subsystem
	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		Subsystem->AddMappingContext(TankMappingContext, 0);
	}

	//Set timer so that based on the fire rate it will shoot at the player
	GetWorldTimerManager().SetTimer(ShootTimeHandle, this, &ATank::EnableShooting, FireRate, true);
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerController)
	{
		const float SphereRadius = 25.f;
		const int SphereSegments = 12;

		FHitResult HitResult;

		PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

		if (bIsDebugMode)
			DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, SphereRadius, SphereSegments, FColor::Red);

		LookAtTarget(HitResult.ImpactPoint, TurretRotationSpeed);

	}
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	
	if (EIC)
	{
		EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATank::MoveHandler);
		EIC->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ATank::TurnHandler);
		EIC->BindAction(ShootAction, ETriggerEvent::Triggered, this, &ATank::ShootHandler);
	}
}

void ATank::MoveHandler(const FInputActionValue& Value)
{
	//If we have picked up the speed power up multiply the movement speed by a value
	if (bHasFasterMovement)
	{
		AddMovementInput(GetActorForwardVector() * Value.Get<float>() * GetWorld()->DeltaTimeSeconds *
			MovementSpeed * MovementSpeedMultiplier);
	}
	else
	{
		AddMovementInput(GetActorForwardVector() * Value.Get<float>() * GetWorld()->DeltaTimeSeconds,
						MovementSpeed);
	}
}

void ATank::TurnHandler(const FInputActionValue& Value)
{
	AddControllerYawInput(Value.Get<float>() * GetWorld()->DeltaTimeSeconds * RotationSpeed);
}

void ATank::ShootHandler(const FInputActionValue& Value)
{
	if (bCanShoot)
	{
		Shoot();
		bCanShoot = false;
	}
}

void ATank::EnableShooting()
{
	bCanShoot = true;
}

void ATank::IncreaseHealth(float healthValue)
{
	Health += healthValue;
}

void ATank::EnableFasterMovement(float multiplier, float time)
{
	bHasFasterMovement = true;
	MovementSpeedMultiplier = multiplier;
	
	//Set timer for disabling tanks faster movement
	GetWorldTimerManager().SetTimer(SpeedTimerHandle, this, &ATank::DisableFasterMovement, time, false);
}

void ATank::DisableFasterMovement()
{
	bHasFasterMovement = false;
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();

	if (TimeTrailsGM)
	{
		//Player has died so end game
		TimeTrailsGM->EndGame(false);
	}
	else if (WaveModeGM)
	{
		//Player has died so end game
		WaveModeGM->EndGame();
	}
	
	
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	bIsAlive = false;
}

