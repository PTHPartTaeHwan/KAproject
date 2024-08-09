// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/KAPlayerController.h"

void AKAPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly InputModeGameOnly;
	SetInputMode(InputModeGameOnly);
}
