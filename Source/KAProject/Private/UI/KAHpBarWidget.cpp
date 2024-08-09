// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/KAHpBarWidget.h"

#include "Components/ProgressBar.h"
#include "Interface/KACharacterWidgetInterface.h"

UKAHpBarWidget::UKAHpBarWidget(const FObjectInitializer& ObjectInitializer)
{
	MaxHp = -1.0f;
}

void UKAHpBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HpProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PbHpBar")));
	ensure(HpProgressBar);

	IKACharacterWidgetInterface* CharacterWidget = Cast<IKACharacterWidgetInterface>(OwningActor);
	if (CharacterWidget)
	{
		CharacterWidget->SetupCharacterWidget(this);
	}
}

void UKAHpBarWidget::UpdateHpBar(float NewCurrentHp)
{
	ensure(MaxHp > 0.0f);
	if (HpProgressBar)
	{
		HpProgressBar->SetPercent(NewCurrentHp / MaxHp);
	}
}
