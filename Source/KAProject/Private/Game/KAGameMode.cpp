// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/KAGameMode.h"

// #include "Player/KAPlayerController.h"

AKAGameMode::AKAGameMode()
{
	//DefaultPawnClass
    //PlayerControllerClasee 를 설정해 주어야 함

	// static ConstructorHelpers::FClassFinder<APawn> ThirdPersonClassRef(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter.BP_ThirdPersonCharacter_C"));
	// if (ThirdPersonClassRef.Class)
	// {
	// 	DefaultPawnClass = ThirdPersonClassRef.Class;
	// }

	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassRef(TEXT("/Script/Engine.Blueprint'/Game/KA/Blueprint/BP_KACharacterPlayer.BP_KACharacterPlayer_C'"));
	if (DefaultPawnClassRef.Class)
	{
		DefaultPawnClass = DefaultPawnClassRef.Class;
	}

	// KAPlayerController 를 추가했을 경우 아래처럼 진행 가능
	// PlayerControllerClass = AKAPlayerController::StaticClass();
	
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Script/KAProject.KAPlayerController"));
	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}
}
