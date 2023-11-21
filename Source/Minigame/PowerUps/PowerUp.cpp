// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUp.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Minigame/GameModes/WaveGameMode.h"
#include "Minigame/Pawns/Tank/Tank.h"

// Sets default values
APowerUp::APowerUp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Create the Niagara component
	NiagaraSystemComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraSystemComponent"));
	
	// Attach the Niagara component to the root component
	RootComponent = NiagaraSystemComponent;

	//Set up the collision for the power up
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereComponent->SetCollisionProfileName("Trigger");
	SphereComponent->SetupAttachment(NiagaraSystemComponent);
}

// Called when the game starts or when spawned
void APowerUp::BeginPlay()
{
	Super::BeginPlay();

	//Set up dynamic delegate
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &APowerUp::OnOverlapBegin);

	//Get wave game mode
	WaveGameMode = Cast<AWaveGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	//Get reference to the tank
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

// Called every frame
void APowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APowerUp::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Begin Overlap"));

	if (PickupSound)
	{
		//Play pickup sound when overlap
		UGameplayStatics::PlaySoundAtLocation(this, PickupSound,
			GetActorLocation(), GetActorRotation(), PickupSoundVolume, PickupSoundPitch);
	}

}


