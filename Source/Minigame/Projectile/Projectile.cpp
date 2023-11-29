// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Minigame/Pawns/TankAI/BaseAI.h"
#include "Minigame/Pawns/Turret/Turret.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile"));
	RootComponent = ProjectileMesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));

	//Set properties for the projectile
	if (ProjectileMovement)
	{
		ProjectileMovement->InitialSpeed = InitialSpeed;
		ProjectileMovement->MaxSpeed = MaxSpeed;
		InitialLifeSpan = LifeSpan;
	}

	TrailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke trail particles"));
	TrailParticles->SetupAttachment(ProjectileMesh);

	ProjectileMesh->SetNotifyRigidBodyCollision(true);
	
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	//Add event for when the projectile hits something
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	if (LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound,
			GetActorLocation(), GetActorRotation(), LaunchVolume, LaunchPitch);
	}
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult)
{
	AActor* CurrentOwner = GetOwner();
	
	
	//If we dont have a current owner destroy the projectile
	if (!CurrentOwner)
	{
		Destroy();
		return;
	}

	//Get the instigator of the projectile
	AController* CurrentInstigator = CurrentOwner->GetInstigatorController();
	
	//If the actor is not it self apply damage
	if (OtherActor && OtherActor != this && OtherActor != CurrentOwner)
	{		
		bool bIsAIController = CurrentInstigator && !CurrentInstigator->IsPlayerController();
		bool bIsTurretActor = OtherActor->GetClass()->IsChildOf(ATurret::StaticClass());
		bool bIsTankAIActor = OtherActor->GetClass()->IsChildOf(ABaseAI::StaticClass());
		
		//Return if the turret is shooting another controller
		if (bIsAIController && bIsTurretActor)
		{
			Destroy();
			return;
		}

		if (bIsTankAIActor && bIsAIController)
		{
			Destroy();
			return;
		}
		
		//Apply damage to current instigator
		UGameplayStatics::ApplyDamage(
			OtherActor, //actor that will be damaged
			Damage, //the base damage to apply
			CurrentInstigator, //controller that caused the damage 
			this, //Actor that actually caused the damage
			UDamageType::StaticClass() //class that describes the damage that was done
		);

		if (HitParticles)
		{
			//Spawn hit particles at the location and rotation
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(),
				GetActorRotation());
		}

		if (HitSound)
		{
			//Play sound at location
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation(),
				GetActorRotation(), HitSoundVolume, HitSoundPitch);
		}
	}

	//destroy the actor anyway
	Destroy();
	

}



