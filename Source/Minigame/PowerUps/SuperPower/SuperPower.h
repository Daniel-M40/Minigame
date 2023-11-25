// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Minigame/PowerUps/PowerUp.h"
#include "SuperPower.generated.h"

UCLASS()
class MINIGAME_API ASuperPower : public APowerUp
{
	GENERATED_BODY()

#pragma region Properties

private:
	
	class ATankController* PlayerController;

	UPROPERTY(EditAnywhere, Category="Config")
	TSubclassOf<class ASuperTank> SuperTankClass;
	
	UPROPERTY(EditAnywhere, Category="Config")
	float Duration = 10.f;

public:
	
#pragma endregion 
	
public:
	// Sets default values for this actor's properties
	ASuperPower();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
