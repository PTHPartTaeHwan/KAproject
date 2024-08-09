// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "KAWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class KAPROJECT_API UKAWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

protected:
	virtual void InitWidget() override;
};
