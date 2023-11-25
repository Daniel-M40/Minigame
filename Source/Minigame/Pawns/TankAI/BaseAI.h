// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseAI.generated.h"

UCLASS()
class MINIGAME_API ABaseAI : public ACharacter
{
	GENERATED_BODY()

#pragma region Properties

private:
	//Spawn point of the projectiles
	UPROPERTY(EditAnywhere, Category="Projectile")
	class USceneComponent* ProjectileSpawnPoint;

	//Stores the class of the projectile so we can spawn it
	UPROPERTY(EditAnywhere, Category="Projectile")
	TSubclassOf<class AProjectile> ProjectileClass;

	//Collision component to set hit / trigger events on
	UPROPERTY(EditAnywhere, Category="Collision")
	class USphereComponent* CollisionSphere;

	//Stores the particles used when actor is destroyed
	UPROPERTY(EditAnywhere, Category="Particles", meta=(DisplayName="Death particles"))
	class UParticleSystem* DeathParticles;
	
	//Stores the sound used when actor dies
	UPROPERTY(EditAnywhere, Category="Sound")
	class USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, Category="Sound")
	float DeathSoundVolume = 1.f;

	UPROPERTY(EditAnywhere, Category="Sound")
	float DeathSoundPitch = 1.f;
	
protected:
	//Actor Base Mesh
	UPROPERTY(EditAnywhere, Category="Mesh")
	class UStaticMeshComponent* BaseTurretMesh;

	//Actor tower mesh
	UPROPERTY(EditAnywhere, Category="Mesh")
	UStaticMeshComponent* BaseTowerMesh;

	//Health of the actor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties", meta=(DisplayName="Actor Total Health"))
	float Health = 30.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties", meta=(DisplayName="Actor Max Health"))
	float MaxHealth = 30.f;

	
	//Rotation speed of the turret
	UPROPERTY(EditAnywhere, Category="Movement", meta=(DisplayName="Turrent Roation Speed"))
	float TurretRotationSpeed = 10.f;

	//Game mode refs
	class ATimeTrailsGameMode* TimeTrailsGM;
	
	class AWaveGameMode* WaveModeGM;

	//Movement speed of enemy
	UPROPERTY(EditAnywhere, Category="Movement")
	float MovementSpeed = 0.1f;

	class ATank* Tank;
	
	UPROPERTY(EditAnywhere, Category = "Tower Config")
	float FireRate = 2.f;

	UPROPERTY(EditAnywhere, Category = "Tower Config", meta = (DisplayName = "Turret Range"))
	float FireRange = 10.f;

	//Timer handle for setting a delay on when the turret can shoot
	FTimerHandle TimerHandle;
	
	FTimerHandle RefreshPawnHandle;

	float RefreshPawnTime = 2.5;


public:
	//Range in which the actor stays away from the tank by
	UPROPERTY(EditAnywhere, Category="Movement")
	float Range = 500.f;

	
#pragma endregion

public:
	// Sets default values for this character's properties
	ABaseAI();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Shoot();

	void LookAtTarget(const FVector& LookAtTarget, const float RotateSpeed = 10.f);

	virtual void HandleDestruction();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void IncreaseStats(const float SpeedIncrement, const float FireRateDecrease);

	// Called when the actor takes damage
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	//Check if the actor can fire
	void CheckFireCondition();

	//Is actor in range of turret
	bool IsActorInRange(const FVector& ActorLocation);

	void ResetTimer();

	void GetPlayerPawn();
	
};
