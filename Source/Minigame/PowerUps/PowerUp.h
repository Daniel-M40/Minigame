﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerUp.generated.h"

UCLASS()
class MINIGAME_API APowerUp : public AActor
{
	GENERATED_BODY()

#pragma region Properties
private:
	UPROPERTY(EditAnywhere, Category = "Particles")
	class UNiagaraComponent* NiagaraSystemComponent;

	UPROPERTY(EditAnywhere, Category = "Particles")
	class UNiagaraSystem* NiagaraSystemAsset;
	
	UPROPERTY(EditAnywhere, Category="Config")
	class USphereComponent* SphereComponent;

protected:
	UPROPERTY(EditAnywhere, Category="Sound")
	class USoundBase* PickupSound;

	UPROPERTY(EditAnywhere, Category="Sound")
	float PickupSoundVolume = 1.f;

	UPROPERTY(EditAnywhere, Category="Sound")
	float PickupSoundPitch = 1.f;
	
#pragma endregion
	
public:
	// Sets default values for this actor's properties
	APowerUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};