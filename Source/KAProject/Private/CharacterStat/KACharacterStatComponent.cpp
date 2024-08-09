// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStat/KACharacterStatComponent.h"

// Sets default values for this component's properties
UKACharacterStatComponent::UKACharacterStatComponent()
{
	MaxHp = 200.0f;
	CurrentHp = MaxHp;
}

// Called when the game starts
void UKACharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	SetHp(MaxHp);
}

float UKACharacterStatComponent::ApplyDamage(float InDamage)
{
	const float PrevHp = CurrentHp;
	const float ActualDamage = FMath::Clamp<float>(InDamage, 0, InDamage);

	SetHp(PrevHp - ActualDamage);
	if (CurrentHp <= KINDA_SMALL_NUMBER)
	{
		OnHpZero.Broadcast();	
	}

	return ActualDamage;
}

void UKACharacterStatComponent::SetHp(float NewHp)
{
	CurrentHp = FMath::Clamp<float>(NewHp, 0.0f, MaxHp);

	OnHpChangeDelegate.Broadcast(CurrentHp);
}



