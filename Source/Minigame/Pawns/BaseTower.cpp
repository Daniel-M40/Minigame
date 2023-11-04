// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTower.h"

#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABaseTower::ABaseTower()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create components and set up attachments
	BaseTowerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tower Mesh"));
	RootComponent = BaseTowerMesh;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	CollisionSphere->SetupAttachment(BaseTowerMesh);
	
	BaseTurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	BaseTurretMesh->SetupAttachment(BaseTowerMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));

}

// Called when the game starts or when spawned
void ABaseTower::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseTower::Shoot()
{
	//Spawn projectile here
}

void ABaseTower::LookAtTarget(const FVector& LookAtTarget, const float RotateSpeed)
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
}

// Called every frame
void ABaseTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABaseTower::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

