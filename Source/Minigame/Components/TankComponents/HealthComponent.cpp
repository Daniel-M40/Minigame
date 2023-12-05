// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Minigame/GameModes/TimeTrailsGameMode.h"
#include "Minigame/GameModes/WaveGameMode.h"
#include "Minigame/Pawns/BasePawn.h"
#include "Minigame/Pawns/Tank/Tank.h"
#include "Minigame/Pawns/TankAI/BaseAI.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	//Set current health
	CurrentHealth = MaxHealth;
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::SetHealth(float health)
{
	CurrentHealth = health;
}

float UHealthComponent::GetHealth()
{
	return CurrentHealth;
}

void UHealthComponent::IncreaseHealth(float healthIncrement)
{
	//if actor hasn't reached the max health value increase health
	if (CurrentHealth < MaxHealth)
	{
		CurrentHealth += healthIncrement;
		UE_LOG(LogTemp, Warning, TEXT("New health val: %f"), CurrentHealth);
	}
}

void UHealthComponent::DecreaseHealth(float damageDelt)
{
	AActor* owner = GetOwner();
	
	ATank* tank = Cast<ATank>(owner);
	ABaseAI* tankAI = Cast<ABaseAI>(owner);

	//Deal damage
	CurrentHealth -= damageDelt;
	
	if (CurrentHealth <= 0.f)
	{
		//Destroy actor
		if (tankAI)
		{
			tankAI->HandleDestruction();
		}
		else if (tank)
		{
			tank->HandleDestruction();
		}
	}

}

