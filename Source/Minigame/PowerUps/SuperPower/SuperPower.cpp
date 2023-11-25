// Fill out your copyright notice in the Description page of Project Settings.


#include "SuperPower.h"

#include "Kismet/GameplayStatics.h"
#include "Minigame/Controllers/Player/TankController.h"
#include "Minigame/GameModes/WaveGameMode.h"
#include "Minigame/Pawns/Tank/Tank.h"


// Sets default values
ASuperPower::ASuperPower()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASuperPower::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASuperPower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASuperPower::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	UE_LOG(LogTemp, Warning, TEXT("Super power up overlap"));

	//Check if actor is a kind of tank
	if (OtherActor->GetClass()->IsChildOf(ATank::StaticClass()))
	{
		if (!WaveGameMode->bSpawningTank)
		{
			WaveGameMode->SpawnSuperTank(Tank, SuperTankClass, Duration);		
		}

		//Destroy power up after pickup
		Destroy();
		
	}
}

