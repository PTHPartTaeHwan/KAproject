// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/KACharacterPlayer.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Camera/CameraComponent.h"
#include "Character/KACharacterControlData.h"
#include "GameFramework/SpringArmComponent.h"

AKACharacterPlayer::AKACharacterPlayer()
{
	// Camera
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // 스프링 앞 끝에 자동으로 달라붙는다
	FollowCamera->bUsePawnControlRotation = false;

	// Input
	
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionJumpRef(TEXT("/Script/EnhancedInput.InputAction'/Game/KA/Input/Action/IA_Jump.IA_Jump'"));
	if (nullptr != InputActionJumpRef.Object)
	{
		JumpAction = InputActionJumpRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputChangeActionControlRef(TEXT("/Script/EnhancedInput.InputAction'/Game/KA/Input/Action/IA_ChangeControl.IA_ChangeControl'"));
	if (nullptr != InputChangeActionControlRef.Object)
	{
		ChangeControlAction = InputChangeActionControlRef.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UInputAction> InputShoulderActionMoveRef(TEXT("/Script/EnhancedInput.InputAction'/Game/KA/Input/Action/IA_ShoulderMove.IA_ShoulderMove'"));
	if (nullptr != InputShoulderActionMoveRef.Object)
	{
		ShoulderMoveAction = InputShoulderActionMoveRef.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UInputAction> InputShoulderActionLookRef(TEXT("/Script/EnhancedInput.InputAction'/Game/KA/Input/Action/IA_ShoulderLook.IA_ShoulderLook'"));
	if (nullptr != InputShoulderActionLookRef.Object)
	{
		ShoulderLookAction = InputShoulderActionLookRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputQuaterActionMoveRef(TEXT("/Script/EnhancedInput.InputAction'/Game/KA/Input/Action/IA_QuaterMove.IA_QuaterMove'"));
	if (nullptr != InputQuaterActionMoveRef.Object)
	{
		QuaterMoveAction = InputQuaterActionMoveRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputAttackActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/KA/Input/Action/IA_Attack.IA_Attack'"));
	if (nullptr != InputAttackActionRef.Object)
	{
		AttackAction = InputAttackActionRef.Object;
	}

	CurrentCharacterControlType = ECharacterControlType::Quater;
}

void AKACharacterPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	SetCharacterControl(CurrentCharacterControlType);
}

void AKACharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	EnhancedInputComponent->BindAction(ChangeControlAction, ETriggerEvent::Triggered, this, &AKACharacterPlayer::ChangeCharacterControl);
	EnhancedInputComponent->BindAction(ShoulderMoveAction, ETriggerEvent::Triggered, this, &AKACharacterPlayer::ShoulderMove);
	EnhancedInputComponent->BindAction(ShoulderLookAction, ETriggerEvent::Triggered, this, &AKACharacterPlayer::ShoulderLook);
	EnhancedInputComponent->BindAction(QuaterMoveAction, ETriggerEvent::Triggered, this, &AKACharacterPlayer::QuaterMove);	
	EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AKACharacterPlayer::Attack);	
}

void AKACharacterPlayer::ChangeCharacterControl()
{
	if (CurrentCharacterControlType == ECharacterControlType::Quater)
	{
		SetCharacterControl(ECharacterControlType::Shoulder);
	}
	else if (CurrentCharacterControlType == ECharacterControlType::Shoulder)
	{
		SetCharacterControl(ECharacterControlType::Quater);
	}
}

void AKACharacterPlayer::SetCharacterControl(ECharacterControlType NewCharacterControlType)
{
	UKACharacterControlData* NewCharacterControl = CharacterControlManager[NewCharacterControlType];

	SetCharacterControlData(NewCharacterControl);

	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();
		UInputMappingContext* NewMappingContext = NewCharacterControl->InputMappingContext;
		if (NewMappingContext)
		{
			Subsystem->AddMappingContext(NewMappingContext, 0);
		}
	}

	CurrentCharacterControlType = NewCharacterControlType;
}

void AKACharacterPlayer::SetCharacterControlData(const UKACharacterControlData* CharacterControlData)
{
	Super::SetCharacterControlData(CharacterControlData);

	CameraBoom->TargetArmLength = CharacterControlData->TargetArmLength;
	CameraBoom->SetRelativeRotation(CharacterControlData->RelativeRotation);
	CameraBoom->bUsePawnControlRotation = CharacterControlData->bUsePawnControlRotation;
	CameraBoom->bInheritPitch = CharacterControlData->bInheritPitch;
	CameraBoom->bInheritYaw = CharacterControlData->bInheritYaw;
	CameraBoom->bInheritRoll = CharacterControlData->bInheritRoll;
	CameraBoom->bDoCollisionTest = CharacterControlData->bDoCollisionTest;
}

void AKACharacterPlayer::ShoulderMove(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection =FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.X);
	AddMovementInput(RightDirection, MovementVector.Y);
}

void AKACharacterPlayer::ShoulderLook(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void AKACharacterPlayer::QuaterMove(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	float InputSizeSquared = MovementVector.SquaredLength();
	float MovementVectorSize = 1.0f;
	float MovementVectorSizeSquared = MovementVector.SquaredLength();
	if (MovementVectorSizeSquared > 1.0f)
	{
		MovementVector.Normalize();
		MovementVectorSizeSquared = 1.0f;
	}
	else
	{
		MovementVectorSize = FMath::Sqrt(MovementVectorSizeSquared);
	}

	FVector MoveDirection = FVector(MovementVector.X, MovementVector.Y, 0.0f);
	GetController()->SetControlRotation(FRotationMatrix::MakeFromX(MoveDirection).Rotator());
	AddMovementInput(MoveDirection, MovementVectorSize);
}

void AKACharacterPlayer::Attack()
{
	ProcessComboCommand();
}
