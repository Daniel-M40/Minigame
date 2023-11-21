// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class MINIGAME_API AProjectile : public AActor
{
	GENERATED_BODY()

	#pragma region Properties

private:
	//Static mesh that we can assign a projectile mesh to
	UPROPERTY(EditDefaultsOnly, Category = "Mesh", meta = (DisplayName = "Projectile Mesh"))
	UStaticMeshComponent* ProjectileMesh;

	//Initial and max speed for the projectile
	UPROPERTY(EditDefaultsOnly, Category = "Config", meta = (DisplayName = "Initial Speed"))
	float InitialSpeed = 1300.f;

	UPROPERTY(EditDefaultsOnly, Category = "Config", meta = (DisplayName = "Max Speed"))
	float MaxSpeed = 1300.f;

	UPROPERTY(EditDefaultsOnly, Category = "Config", meta = (DisplayName = "Life Span"))
	float LifeSpan = 5.f;

	//Projectile movement component, allows us to set the life span and speed
	UPROPERTY(VisibleAnywhere, Category = "Config", meta = (DisplayName = "Projectile Mesh"))
	class UProjectileMovementComponent* ProjectileMovement;

	//Damage dealt from projectile
	UPROPERTY(EditAnywhere)
	float Damage = 10.f;


	//Particles that are used for when the projectile has collided with an actor
	UPROPERTY(EditAnywhere, Category="Combat", meta=(DisplayName="Hit particles"))
	class UParticleSystem* HitParticles;

	//Particles used for when the projectile is in the air 
	UPROPERTY(VisibleAnywhere, Category="Combat", meta=(DisplayName="Trail Particles"))
	class UParticleSystemComponent* TrailParticles;

	UPROPERTY(EditAnywhere, Category="Combat")
	class USoundBase* LaunchSound;

	UPROPERTY(EditAnywhere, Category="Sound")
	float LaunchVolume = .4f;

	UPROPERTY(EditAnywhere, Category="Sound")
	float LaunchPitch = 1.f;
	
	UPROPERTY(EditAnywhere, Category="Sound")
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category="Sound")
	float HitSoundVolume = 1.f;

	UPROPERTY(EditAnywhere, Category="Sound")
	float HitSoundPitch = 1.f;	
	#pragma endregion
	
public:
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Handle damage and particle effects
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult);
};
