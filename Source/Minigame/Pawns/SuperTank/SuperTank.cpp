// Fill out your copyright notice in the Description page of Project Settings.


#include "SuperTank.h"


// Sets default values
ASuperTank::ASuperTank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASuperTank::BeginPlay()
{
	Super::BeginPlay();

	InfiniteFireRate = true;
	
}

// Called every frame
void ASuperTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASuperTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
