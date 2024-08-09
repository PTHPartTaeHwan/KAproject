// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_AttackHitCheck.h"
#include "Interface/KAAnimationAttackInterface.h"

void UAnimNotify_AttackHitCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		IKAAnimationAttackInterface* AttackPawn = Cast<IKAAnimationAttackInterface>(MeshComp->GetOwner());
		if (AttackPawn)
		{
			AttackPawn->AttackHitCheck();
		}
	}
}
