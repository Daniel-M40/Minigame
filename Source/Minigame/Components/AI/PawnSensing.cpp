// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnSensing.h"

#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Minigame/Pawns/Tank/Tank.h"
#include "Minigame/Pawns/TankAI/BaseAI.h"


// Sets default values for this component's properties
UPawnSensing::UPawnSensing()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UPawnSensing::BeginPlay()
{
	Super::BeginPlay();
	
	
}


// Called every frame
void UPawnSensing::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UPawnSensing::SensePawn(APawn& Pawn)
{
	Super::SensePawn(Pawn);

	// Get the player pawn
	ATank* Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	ABaseAI* TankAI = Cast<ABaseAI>(GetOwner()); 
	AAIController* AIController = Cast<AAIController>(TankAI->GetController());

	if (Tank && AIController)
	{
		//Get actor location
		FVector	CurrentLocation = TankAI->GetActorLocation();
	
		//Get tank location
		FVector TankLocation = Tank->GetActorLocation();

		//Find the distance of the tank
		const float Distance = FVector::Dist(TankLocation, CurrentLocation);
		
		//If actor is not in range move to the tank
		if (Distance >= TankAI->Range)
		{
			// Move towards the player's location
			 AIController->MoveToLocation(Tank->GetActorLocation());
		}
	}
}

