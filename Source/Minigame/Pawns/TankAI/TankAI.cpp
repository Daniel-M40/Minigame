// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAI.h"

#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "Minigame/Pawns/Tank/Tank.h"

//Move enemy tank to player tank location
void ATankAI::MoveTankAI()
{
	if (Tank)
	{
		//Get actor location
		FVector	CurrentLocation = GetActorLocation();
	
		//Get tank location
		FVector TankLocation = Tank->GetActorLocation();

		//Find the distance of the tank
		const float Distance = FVector::Dist(TankLocation, CurrentLocation);

		//If actor is not in range move to the tank
		if (Distance >= Range)
		{
			//Move to location
			/*SetActorLocation(
				FMath::VInterpTo(
					CurrentLocation, //Actors current location
					TankLocation, //Tanks current location (target location)
					GetWorld()->GetDeltaSeconds(), //Delta time
					MovementSpeed)
			);*/

			/*AIController = Cast<AAIController>(GetController());

			AIController->MoveToLocation(TankLocation);*/
		}
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
	
	MoveTankAI();
	
}

// Called to bind functionality to input
void ATankAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATankAI::IncreaseStats(const float SpeedIncrement, const float FireRateDecrease)
{
	//Increase enemy status after wave is completed
	MovementSpeed = SpeedIncrement;
	
	//Fire rate cannot be less than 0 other wise it wont trigger the function
	if (FireRate <= 0.f)
	{
		FireRate = 0.f;
	}
	else
	{
		FireRate = FireRateDecrease;
	}
}

void ATankAI::HandleDestruction()
{
	Super::HandleDestruction();
}


