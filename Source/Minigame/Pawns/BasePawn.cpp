// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

#include "Components/SphereComponent.h"
#include "Evaluation/IMovieSceneEvaluationHook.h"
#include "Kismet/GameplayStatics.h"
#include "Minigame/GameModes/TimeTrailsGameMode.h"
#include "Minigame/GameModes/WaveGameMode.h"
#include "Minigame/Projectile/Projectile.h"
#include "TankAI/TankAI.h"
#include "Turret/Turret.h"


// Sets default values
ABasePawn::ABasePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create components and set up attachments
	BaseTowerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tower Mesh"));
	RootComponent = BaseTowerMesh;

	//Collision component
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	CollisionSphere->SetupAttachment(BaseTowerMesh);
	CollisionSphere->SetCollisionProfileName("Trigger");

	//Turret mesh
	BaseTurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	BaseTurretMesh->SetupAttachment(BaseTowerMesh);

	//Projectile spawn point
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(BaseTurretMesh);

	

	
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	
	//Assign game modes
	TimeTrailsGM = Cast<ATimeTrailsGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	WaveModeGM = Cast<AWaveGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

void ABasePawn::Shoot()
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

void ABasePawn::LookAtTarget(const FVector& LookAtTarget, const float RotateSpeed)
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

	//If class is Tank AI then rotate the base tower mesh as well as the turret
	if (GetClass()->IsChildOf(ATankAI::StaticClass()))
	{
		BaseTowerMesh->SetWorldRotation(
		FMath::RInterpTo(BaseTowerMesh->GetComponentRotation(),
			LookAtRotation,
			UGameplayStatics::GetWorldDeltaSeconds(this),
			RotateSpeed));
	}
	
}


void ABasePawn::HandleDestruction()
{
	//Visual / Sound effects
	if (DeathParticles)
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetActorLocation(), GetActorRotation());
	

	if (DeathSound)
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());

	
	Destroy();
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float ABasePawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
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



