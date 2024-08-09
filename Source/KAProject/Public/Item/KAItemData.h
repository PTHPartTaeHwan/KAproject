// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "KAItemData.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Weapon = 0,
	Potion,
	Scroll
};

/**
 * 
 */
UCLASS()
class KAPROJECT_API UKAItemData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Type)
	EItemType Type;
};
