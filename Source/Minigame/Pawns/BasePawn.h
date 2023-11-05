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

protected:
	UPROPERTY(EditAnywhere, Category="Properties")
	class UStaticMeshComponent* BaseTurretMesh;

	UPROPERTY(EditAnywhere, Category="Properties")
	UStaticMeshComponent* BaseTowerMesh;

	UPROPERTY(EditAnywhere, Category="Properties")
	class USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, Category="Properties")
	class USphereComponent* CollisionSphere;

	UPROPERTY(EditAnywhere, Category="Properties", meta=(DisplayName="Turrent Roation Speed"))
	float TurretRotationSpeed = 10.f;
	
	UPROPERTY(EditAnywhere, Category="Properties")
	TSubclassOf<AProjectile> ProjectileClass;
	
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

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	
#pragma endregion
};
