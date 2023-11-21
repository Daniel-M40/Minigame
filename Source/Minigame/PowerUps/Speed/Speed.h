// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Minigame/PowerUps/PowerUp.h"
#include "Speed.generated.h"

UCLASS()
class MINIGAME_API ASpeed : public APowerUp
{
	GENERATED_BODY()

#pragma region Properties
	
private:
	UPROPERTY(EditAnywhere, Category="Config")
	float SpeedIncreaseDuration = 5.f;

	UPROPERTY(EditAnywhere, Category="Config")
	float Multiplier = 5.f;
	
#pragma endregion

#pragma region Properties
	
public:
	// Sets default values for this actor's properties
	ASpeed();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

#pragma endregion
};
