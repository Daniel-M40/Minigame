// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"

#include "Kismet/GameplayStatics.h"
#include "Minigame/Pawns/Tank/Tank.h"


// Sets default values
ATurret::ATurret()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	//Set timer so that based on the fire rate it will shoot at the player
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATurret::CheckFireCondition, FireRate, true);
	
}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Tank)
	{
		//Get tank location
		const FVector tankCurrentLocation = Tank->GetActorLocation();

		//If tank is in range
		if (IsActorInRange(tankCurrentLocation))
		{
			//Look at player location
			LookAtTarget(tankCurrentLocation, mTurretRotationSpeed);
		}
	}
}

// Called to bind functionality to input
void ATurret::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATurret::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATurret::CheckFireCondition()
{
	if (Tank)
	{
		const FVector tankCurrentLocation = Tank->GetActorLocation();
		
		//Fire at the tank if it is in range and alive
		if (IsActorInRange(tankCurrentLocation) && Tank->bIsAlive)
		{
			Shoot();
		}
	}
}

bool ATurret::IsActorInRange(const FVector& ActorLocation)
{
	const FVector towerCurrentLocation = GetActorLocation();

	//Find the distance of the tank
	const float Distance = FVector::Dist(towerCurrentLocation, ActorLocation);

	//Check if the tank is in range
	return Distance <= mFireRange;
}

