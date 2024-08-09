// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/KATestBoxMan.h"

// Sets default values
AKATestBoxMan::AKATestBoxMan()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//CDO 생성
//	Head, Body, Left, Right
	Head = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Head"));
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Left = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left"));
	Right = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right"));

	RootComponent = Body;
	Head->SetupAttachment(Body);
	Left->SetupAttachment(Body);
	Right->SetupAttachment(Body);

	Head->SetRelativeLocation(FVector(0.0f,0.0f,100.0f));
	Left->SetRelativeLocation(FVector(60.0f,0.0f,0.0f));
	Right->SetRelativeLocation(FVector(-60.0f,0.0f,0.0f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BodyMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
    if (BodyMeshRef.Object)
    {
    	Body->SetStaticMesh(BodyMeshRef.Object);
    }

	static ConstructorHelpers::FObjectFinder<UStaticMesh> HeadMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (BodyMeshRef.Object)
	{
		Head->SetStaticMesh(BodyMeshRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> LeftMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (BodyMeshRef.Object)
	{
		Left->SetStaticMesh(BodyMeshRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> RightMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (BodyMeshRef.Object)
	{
		Right->SetStaticMesh(BodyMeshRef.Object);
	}

	Body->SetRelativeScale3D(FVector(0.5f,0.5f,0.5f));
	Head->SetRelativeScale3D(FVector(0.5f,0.5f,0.5f));
	Left->SetRelativeScale3D(FVector(0.5f,0.5f,0.5f));
	Right->SetRelativeScale3D(FVector(0.5f,0.5f,0.5f));
}

// Called when the game starts or when spawned
void AKATestBoxMan::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKATestBoxMan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

