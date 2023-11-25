// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAI.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Minigame/GameModes/TimeTrailsGameMode.h"
#include "Minigame/GameModes/WaveGameMode.h"
#include "Minigame/Pawns/Tank/Tank.h"
#include "Minigame/Projectile/Projectile.h"


// Sets default values
ABaseAI::ABaseAI()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Create components and set up attachments
	BaseTowerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tower Mesh"));
	BaseTowerMesh->SetupAttachment(RootComponent);

	//Turret mesh
	BaseTurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	BaseTurretMesh->SetupAttachment(BaseTowerMesh);
	
	//Projectile spawn point
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(BaseTurretMesh);
}

// Called when the game starts or when spawned
void ABaseAI::BeginPlay()
{
	Super::BeginPlay();

	//Assign game modes
	TimeTrailsGM = Cast<ATimeTrailsGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	WaveModeGM = Cast<AWaveGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	//Set timer so that based on the fire rate it will shoot at the player
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABaseAI::CheckFireCondition, FireRate, true);

	
}

void ABaseAI::Shoot()
{
	//Spawn projectile
	if (ProjectileClass)
	{
		AProjectile* tempProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,
																	  ProjectileSpawnPoint->GetComponentLocation(),
																	  ProjectileSpawnPoint->GetComponentRotation());
		tempProjectile->SetOwner(this);
	}
}

void ABaseAI::LookAtTarget(const FVector& LookAtTarget, const float RotateSpeed)
{
	//Get target location Mouse location - Current Location
	const FVector ToTarget = LookAtTarget - BaseTurretMesh->GetComponentLocation();

	const FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);

	//Update Yaw component for the turret mesh
	BaseTurretMesh->SetWorldRotation(
		FMath::RInterpTo(BaseTurretMesh->GetComponentRotation(),
			LookAtRotation,
			UGameplayStatics::GetWorldDeltaSeconds(this),
			RotateSpeed));

	//Update Yaw component for the tower mesh
	BaseTowerMesh->SetWorldRotation(
		FMath::RInterpTo(BaseTowerMesh->GetComponentRotation(),
			LookAtRotation,
			UGameplayStatics::GetWorldDeltaSeconds(this),
			RotateSpeed));
}

void ABaseAI::HandleDestruction()
{
	//Visual / Sound effects
	if (DeathParticles)
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetActorLocation(), GetActorRotation());
	

	if (DeathSound)
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation(),
			DeathSoundVolume, DeathSoundPitch);

	
	if (TimeTrailsGM)
	{
		//Decrease turret count
		TimeTrailsGM->DecreaseTurretAmount();
	}
	else if (WaveModeGM)
	{
		//Spawn power up at location and rotation
		WaveModeGM->SpawnPowerUp(GetActorLocation(), GetActorRotation());
	}
	
	Destroy();
}

// Called every frame
void ABaseAI::Tick(float DeltaTime)
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
			LookAtTarget(tankCurrentLocation, TurretRotationSpeed);
		}
	}
}

// Called to bind functionality to input
void ABaseAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABaseAI::IncreaseStats(const float SpeedIncrement, const float FireRateDecrease)
{
	//Increase enemy status after wave is completed
	MovementSpeed = SpeedIncrement;
	
	GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;
	
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

float ABaseAI::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                          AActor* DamageCauser)
{
	//Subtract damage from health
	Health -= DamageAmount;

	//Check if actor has died
	if (Health <= 0.f)
	{
		HandleDestruction();
	}
	
	return DamageAmount;
}

void ABaseAI::CheckFireCondition()
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

bool ABaseAI::IsActorInRange(const FVector& ActorLocation)
{
	const FVector towerCurrentLocation = GetActorLocation();

	//Find the distance of the tank
	const float Distance = FVector::Dist(towerCurrentLocation, ActorLocation);

	//Check if the tank is in range
	return Distance <= FireRange;
}

void ABaseAI::ResetTimer()
{
	GetWorldTimerManager().ClearTimer(TimerHandle);

	//Set timer so that based on the fire rate it will shoot at the player
	//Set new timer with new fire rate
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABaseAI::CheckFireCondition, FireRate, true);
}

