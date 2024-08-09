// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/KAItemData.h"
#include "KAWeaponItemData.generated.h"

/**
 * 
 */
UCLASS()
class KAPROJECT_API UKAWeaponItemData : public UKAItemData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = Weapon)
	TSoftObjectPtr<USkeletalMesh> WeaponMesh;
};
