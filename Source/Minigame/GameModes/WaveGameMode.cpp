// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveGameMode.h"

#include "Kismet/GameplayStatics.h"

void AWaveGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	//Hide Mouse Cursor
	UGameplayStatics::GetPlayerController(this, 0)->SetShowMouseCursor(false);
}
