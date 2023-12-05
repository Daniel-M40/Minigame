// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MINIGAME_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

#pragma region Properties

private:
	UPROPERTY(EditAnywhere, Category="Health")
	float MaxHealth = 0.f;
	
	UPROPERTY(EditAnywhere, Category="Health")
	float CurrentHealth = 0.f;

	
#pragma endregion 

#pragma region Actions
	
public:
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetHealth(float health);

	UFUNCTION(BlueprintCallable)
	float GetHealth();
	
	void IncreaseHealth(float healthIncrement);
	
	void DecreaseHealth(float damageDelt);
	
#pragma endregion
};
