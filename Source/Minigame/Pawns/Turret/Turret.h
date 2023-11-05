// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Minigame/Pawns/BasePawn.h"
#include "Turret.generated.h"

UCLASS()
class MINIGAME_API ATurret : public ABasePawn
{
	GENERATED_BODY()

#pragma region Properties

	class ATank* Tank;

	UPROPERTY(EditAnywhere, Category = "Tower Config", meta = (DisplayName = "Turret Range", AllowPrivateAccess = "true"))
	float mFireRange = 10.f;

	UPROPERTY(EditAnywhere, Category = "Tower Config", meta = (DisplayName = "Turret Rotation Speed", AllowPrivateAccess = "true"))
	float mTurretRotationSpeed = 10.f;

	FTimerHandle TimerHandle;
	float FireRate = 2.f;
	
#pragma endregion
	
	
public:
	// Sets default values for this pawn's properties
	ATurret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void HandleDestruction() override;

	void CheckFireCondition();

	bool IsActorInRange(const FVector& ActorLocation);
};
