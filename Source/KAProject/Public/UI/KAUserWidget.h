// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KAUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class KAPROJECT_API UKAUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetOwningActor(AActor* NewOwner) { OwningActor = NewOwner; }

protected:
	UPROPERTY()
	TObjectPtr<AActor> OwningActor;
};
