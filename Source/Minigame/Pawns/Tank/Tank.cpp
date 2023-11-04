// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


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

	//Get Player controller
	PlayerController = Cast<APlayerController>(GetController());

	//If we have player controller assign the mapping context to the subsystem
	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		Subsystem->AddMappingContext(TankMappingContext, 0);
	}

	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
	AddMovementInput(GetActorForwardVector() * Value.Get<float>());
}

void ATank::TurnHandler(const FInputActionValue& Value)
{
	AddControllerYawInput(Value.Get<float>());
}

void ATank::ShootHandler(const FInputActionValue& Value)
{
	Shoot();
}

