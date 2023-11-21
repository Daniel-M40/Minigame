// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Minigame/PowerUps/PowerUp.h"
#include "Health.generated.h"

UCLASS()
class MINIGAME_API AHealth : public APowerUp
{
	GENERATED_BODY()

#pragma region Properties
	
private:
	UPROPERTY(EditAnywhere, Category="Config")
	float HealthIncrease = 10.f;

#pragma endregion

#pragma region Actions
	
public:
	// Sets default values for this actor's properties
	AHealth();

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
