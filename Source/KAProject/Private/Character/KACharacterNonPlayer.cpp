// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/KACharacterNonPlayer.h"

AKACharacterNonPlayer::AKACharacterNonPlayer()
{
}

void AKACharacterNonPlayer::SetDead()
{
	Super::SetDead();
	
	FTimerHandle DeadTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda(
		[&]()
		{
			Destroy();
		}
	), DeadEventDelayTime, false);
}
