// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/KAItemBox.h"

#include "Components/BoxComponent.h"
#include "Interface/KACharacterItemInterface.h"
#include "Particles/ParticleSystemComponent.h"
#include "Physics/KACollision.h"

// Sets default values
AKAItemBox::AKAItemBox()
{
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Effect")); 

	RootComponent = Trigger;
	Mesh->SetupAttachment(Trigger);
	Effect->SetupAttachment(Trigger);

	Trigger->SetCollisionProfileName(CPROFILE_KATRIGGER);
	Trigger->SetBoxExtent(FVector(40.0f, 42.0f, 30.0f));
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AKAItemBox::OnOverlapBegin);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/ArenaBattle/Environment/Props/SM_Env_Breakables_Box1.SM_Env_Breakables_Box1'"));
	if (BoxMeshRef.Object)
	{
		Mesh->SetStaticMesh(BoxMeshRef.Object);
	}
	Mesh->SetRelativeLocation(FVector(0.0f, -3.5f, -30.0f));
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));

	static ConstructorHelpers::FObjectFinder<UParticleSystem> EffectRef(TEXT("/Script/Engine.ParticleSystem'/Game/ArenaBattle/Effect/P_TreasureChest_Open_Mesh.P_TreasureChest_Open_Mesh'"));
	if (EffectRef.Object)
	{
		Effect->SetTemplate(EffectRef.Object);
		Effect->bAutoActivate = false;
	}
}

void AKAItemBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	if (nullptr == Item)
	{
		Destroy();
		return;
	}

	IKACharacterItemInterface* OverlappingPawn = Cast<IKACharacterItemInterface>(OtherActor);
	if (OverlappingPawn)
	{
		OverlappingPawn->TakeItem(Item);
	}

	Effect->Activate(true);
	Mesh->SetHiddenInGame(true);
	SetActorEnableCollision(false);
	Effect->OnSystemFinished.AddDynamic(this, &AKAItemBox::OnEffectFinished);
}

void AKAItemBox::OnEffectFinished(UParticleSystemComponent* ParticleSystem)
{
	Destroy();
}

