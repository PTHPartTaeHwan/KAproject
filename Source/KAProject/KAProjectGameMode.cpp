// Copyright Epic Games, Inc. All Rights Reserved.

#include "KAProjectGameMode.h"
#include "KAProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AKAProjectGameMode::AKAProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
