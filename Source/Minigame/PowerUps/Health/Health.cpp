// Fill out your copyright notice in the Description page of Project Settings.


#include "Health.h"

#include "Kismet/GameplayStatics.h"
#include "Minigame/Pawns/Tank/Tank.h"


// Sets default values
AHealth::AHealth()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHealth::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHealth::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHealth::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Get functionality from parent class
	Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	
	UE_LOG(LogTemp, Warning, TEXT("Health Overlap"));
	
	//Check if actor is a kind of tank
	if (OtherActor->GetClass()->IsChildOf(ATank::StaticClass()))
	{
		//Apply power up to tank
		if (Tank)
		{
			Tank->IncreaseHealth(HealthIncrease);
		}

			
		//Destroy power up after pickup
		Destroy();
	}
}

