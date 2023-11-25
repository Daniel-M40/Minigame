// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Minigame/Controllers/AI/TankAIController.h"
#include "Minigame/Controllers/Player/TankController.h"
#include "Minigame/Pawns/SuperTank/SuperTank.h"
#include "Minigame/Pawns/Tank/Tank.h"
#include "Minigame/PowerUps/PowerUp.h"
#include "Minigame/WaveSpawner/WaveSpawner.h"

AWaveGameMode::AWaveGameMode()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultPawnClass = ATank::StaticClass();

}


void AWaveGameMode::AllWavesComplete()
{
	// Check if all wave spawners are complete
	for (int i = 0; i < WaveSpawnerAmount; i++)
	{
		if (WaveSpawnerArr[i] && !WaveSpawnerArr[i]->bWaveComplete)
		{
			bAllWavesComplete = false; // If any wave spawner is incomplete, set the flag to false
			break; // No need to continue checking, we already know not all waves are complete
		}

		//Otherwise all waves are complete and set flag to true
		bAllWavesComplete = true;
	}

	//If all waves complete spawn enemies again
	if (bAllWavesComplete)
	{
		CurrentWave++;
		CurrentWaveTxt = "Wave: " + FString::FromInt(CurrentWave);

		for (AWaveSpawner* WaveSpawner : WaveSpawnerArr)
		{
			WaveSpawner->StartWave();
		}

		bAllWavesComplete = false;
	}
}

void AWaveGameMode::BeginPlay()
{
	Super::BeginPlay();

	//Add getting all wave spawners on a delay
	GetWorldTimerManager().SetTimer(GetAllWavesTimer, this,
		&AWaveGameMode::GetAllWaveSpawner, GetAllWavesDelay, false);
	

	//Get length of power up array
	PowerUpArrLength = PowerUpArr.Num();
}

void AWaveGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AllWavesComplete();
}

void AWaveGameMode::GetAllWaveSpawner()
{
	TArray<AActor*> tempWaveSpawnerArr;
	WaveSpawnerClass = AWaveSpawner::StaticClass();

	//Get all actors of class of AWaveSpawner
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), WaveSpawnerClass, tempWaveSpawnerArr);


	for (AActor* Actor : tempWaveSpawnerArr)
	{
		if (Actor)
		{
			//Cast actors to wave spawner and add to array
			WaveSpawnerArr.Add(Cast<AWaveSpawner>(Actor));
		}
	}
	
	//Store the amount of wave spawners in the world
	WaveSpawnerAmount = WaveSpawnerArr.Num();

	UE_LOG(LogTemp, Warning, TEXT("Num of waves spawner: %d"), WaveSpawnerAmount);
}

void AWaveGameMode::EndGame()
{
	//Game is over, flag to show the GameOver Widget
	bGameOver = true;

	//Game over text
	EndGameTxt = "Game Over!!";	
	
}

void AWaveGameMode::IncreaseScore()
{
	PlayerScore++;
}

void AWaveGameMode::SpawnPowerUp(const FVector Location, const FRotator Rotation)
{
	//Randomly spawn power up if the value is 1
	const int spawnPowerUp = FMath::RandRange(0, PowerUpSpawnRate);

	if (spawnPowerUp)
	{
		//Randomly pick power up in array
		const int index = FMath::RandRange(0, PowerUpArrLength - 1);
		
		//Spawn power up in location
		if (PowerUpArr[index])
		{
			GetWorld()->SpawnActor<APowerUp>(PowerUpArr[index], Location, Rotation);
		}
		
	}
}

void AWaveGameMode::SpawnSuperTank(ATank* Tank, TSubclassOf<ASuperTank> SuperTankClass, float duration)
{
	//Assign tank to orignal tank
	OriginalTank = Tank;

	//Set flag to show that we are spawning super tank
	bSpawningTank = true;
	
	//hide in game
	if (OriginalTank)
	{
		//Get player controller
		PlayerController = Cast<ATankController>(UGameplayStatics::GetPlayerController(this, 0));
	}

	if (PlayerController && SuperTankClass)
	{
		FActorSpawnParameters SpawnParams;

		// Forces the pawn to spawn even if colliding
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		FVector NewLocation = OriginalTank->GetActorLocation();
		FRotator NewRotation = OriginalTank->GetActorRotation();

		
		//Spawn new pawn
		SuperTank = GetWorld()->SpawnActor<ASuperTank>(SuperTankClass, NewLocation, NewRotation, SpawnParams);
		
		if (SuperTank)
		{
			//Posses super tank
			PlayerController->UnPossess();
			PlayerController->Possess(SuperTank);
			SuperTank->EnableInput(PlayerController);


			OriginalTank->Destroy();

			//Set timer for how long we posses the tank for
			GetWorldTimerManager().SetTimer(PossesTimerHandle, this, &AWaveGameMode::PossesOriginalTank, duration, false);
		}
			
	}
	
}

void AWaveGameMode::PossesOriginalTank()
{
	if (TankClass)
	{
		FActorSpawnParameters SpawnParams;

		// Forces the pawn to spawn even if colliding
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		
		//Get Old pawn location and rotation
		FVector NewLocation = SuperTank->GetActorLocation();
		FRotator NewRotation = SuperTank->GetActorRotation();
		
		
		//Spawn new pawn
		OriginalTank = GetWorld()->SpawnActor<ATank>(TankClass, NewLocation, NewRotation, SpawnParams);
		

		//Possess new pawn
		PlayerController->UnPossess();
		PlayerController->Possess(OriginalTank);
 		OriginalTank->EnableInput(PlayerController);

		SuperTank->Destroy();
		
	}
}

void AWaveGameMode::SwapPawns(APawn* OldPawn, APawn* NewPawn)
{
	if (OldPawn)
	{
		//Hide old pawn
		OldPawn->SetActorHiddenInGame(false);

		//Possess new pawn
		PlayerController->UnPossess();
		PlayerController->Possess(NewPawn);

		//Get Old pawn location and rotation
		FVector NewLocation = OldPawn->GetActorLocation();
		FRotator NewRotation = OldPawn->GetActorRotation();

		//Set new pawn location and rotation to old pawns location
		NewPawn->SetActorLocation(NewLocation);
		NewPawn->SetActorRotation(NewRotation);

		//Show pawn
		NewPawn->SetActorHiddenInGame(true);
		
	}
}
