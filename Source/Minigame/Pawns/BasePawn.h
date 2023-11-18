// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

class AProjectile;

UCLASS()
class MINIGAME_API ABasePawn : public APawn
{
	GENERATED_BODY()

#pragma region Properties

private:
	//Spawn point of the projectiles
	UPROPERTY(EditAnywhere, Category="Projectile")
	class USceneComponent* ProjectileSpawnPoint;

	//Stores the class of the projectile so we can spawn it
	UPROPERTY(EditAnywhere, Category="Projectile")
	TSubclassOf<AProjectile> ProjectileClass;

	//Collision component to set hit / trigger events on
	UPROPERTY(EditAnywhere, Category="Collision")
	class USphereComponent* CollisionSphere;

	//Stores the particles used when actor is destroyed
	UPROPERTY(EditAnywhere, Category="Particles", meta=(DisplayName="Death particles"))
	class UParticleSystem* DeathParticles;
	
	//Stores the sound used when actor dies
	UPROPERTY(EditAnywhere, Category="Sound")
	class USoundBase* DeathSound;


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

	//Rotation speed of the turret
	UPROPERTY(EditAnywhere, Category="Movement", meta=(DisplayName="Turrent Roation Speed"))
	float TurretRotationSpeed = 10.f;

	//Game mode refs
	class ATimeTrailsGameMode* TimeTrailsGM;
	
	class AWaveGameMode* WaveModeGM;
	
#pragma endregion


#pragma region Actions
	
public:
	// Sets default values for this pawn's properties
	ABasePawn();

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

	// Called when the actor takes damage
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	
#pragma endregion
};
