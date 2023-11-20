// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAI.h"

#include "Kismet/GameplayStatics.h"
#include "Minigame/Pawns/Tank/Tank.h"

//Move enemy tank to player tank location
void ATankAI::MoveTo()
{
	if (Tank)
	{
		//Get actor location
		FVector	CurrentLocation = GetActorLocation();
	
		//Get tank location
		FVector TankLocation = Tank->GetActorLocation();

		//Move to location
		SetActorLocation(
			FMath::VInterpTo(
				CurrentLocation, //Actors current location
				TankLocation, //Tanks current location (target location)
				GetWorld()->GetDeltaSeconds(), //Delta time
				MovementSpeed)
		);
	}

}

// Sets default values
ATankAI::ATankAI()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	

}

// Called when the game starts or when spawned
void ATankAI::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATankAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	MoveTo();
	
}

// Called to bind functionality to input
void ATankAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATankAI::IncreaseStats(const float HealthIncrement,const float SpeedIncrement, const float FireRateDecrease)
{
	//Increase enemy status after wave is completed
	Health += HealthIncrement;
	MovementSpeed += SpeedIncrement;
	FireRate -= FireRateDecrease;
}

