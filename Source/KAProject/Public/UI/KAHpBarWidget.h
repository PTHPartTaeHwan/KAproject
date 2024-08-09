// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/KAUserWidget.h"
#include "KAHpBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class KAPROJECT_API UKAHpBarWidget : public UKAUserWidget
{
	GENERATED_BODY()

public:
	UKAHpBarWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	FORCEINLINE void SetMaxHp(float NewMaxHp) { MaxHp = NewMaxHp; }
	void UpdateHpBar(float NewCurrentHp);

protected:
	UPROPERTY()
	TObjectPtr<class UProgressBar> HpProgressBar;

	UPROPERTY()
	float MaxHp;
};
