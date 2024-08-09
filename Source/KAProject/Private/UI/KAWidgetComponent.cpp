// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/KAWidgetComponent.h"

#include "UI/KAUserWidget.h"

void UKAWidgetComponent::InitWidget()
{
	Super::InitWidget();

	UKAUserWidget* KAUserWidget = Cast<UKAUserWidget>(GetWidget());
	if (KAUserWidget)
	{
		KAUserWidget->SetOwningActor(GetOwner());
	}
}
