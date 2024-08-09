// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/KACharacterBase.h"
#include "KACharacterNonPlayer.generated.h"

/**
 * 
 */
UCLASS()
class KAPROJECT_API AKACharacterNonPlayer : public AKACharacterBase
{
	GENERATED_BODY()

public:
	AKACharacterNonPlayer();

protected:
	void SetDead() override;
};
