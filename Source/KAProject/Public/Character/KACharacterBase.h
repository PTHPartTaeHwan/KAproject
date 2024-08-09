// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/KAAnimationAttackInterface.h"
#include "Interface/KACharacterItemInterface.h"
#include "Interface/KACharacterWidgetInterface.h"
#include "KACharacterBase.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogKACharacter, Log, All);

UENUM()
enum class ECharacterControlType : uint8
{
	Shoulder,
	Quater
};

DECLARE_DELEGATE_OneParam(FOnTakeItemDelegate, class UKAItemData* /*InItemData*/);
USTRUCT(BlueprintType)
struct FTakeItemDelegateWrapper
{
	GENERATED_BODY()
	FTakeItemDelegateWrapper() {}
	FTakeItemDelegateWrapper(const FOnTakeItemDelegate& InItemDelegate) :ItemDelegate(InItemDelegate) {}
	FOnTakeItemDelegate ItemDelegate;	
};

UCLASS()
class KAPROJECT_API AKACharacterBase : public ACharacter, public IKAAnimationAttackInterface, public IKACharacterWidgetInterface, public IKACharacterItemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AKACharacterBase();

	virtual void PostInitializeComponents() override;
	
protected:
	virtual void SetCharacterControlData(const class UKACharacterControlData* CharacterControlData);

	UPROPERTY(EditAnywhere, Category = CharacterControl, meta = (AllowPrivateAccess = "true"))
	TMap<ECharacterControlType, UKACharacterControlData*> CharacterControlManager;

// Combo Action Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> ComboActionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UKAComboActionData> ComboActionData;

	void ProcessComboCommand();

	void ComboActionBegin();
	void ComboActionEnd(class UAnimMontage* TargetMontage, bool IsProperlyEnded);
	void SetComboCheckTimer();
	void ComboCheck();

	int32 CurrentCombo = 0;
	FTimerHandle ComboTimerHandle;
	bool HasNextComboCommand = false;

// Attack Hit Section
protected:
	virtual void AttackHitCheck() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	// Dead Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> DeadMontage;

	virtual void SetDead();
	void PlayDeadAnimation();

	float DeadEventDelayTime = 5.0f;

	// Stat Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = STAT, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UKACharacterStatComponent> Stat;
// UI Widget Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UWidgetComponent> HpBar;

	virtual void SetupCharacterWidget(class UKAUserWidget* InUserWidget) override;

	// Item Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USkeletalMeshComponent> Weapon;

	UPROPERTY()
	TArray<FTakeItemDelegateWrapper> TakeItemActions;

	virtual void TakeItem(class UKAItemData* InItemData) override;
	virtual void DrinkPotion(class UKAItemData* InItemData);
	virtual void EquipWeapon(class UKAItemData* InItemData);
	virtual void ReadScroll(class UKAItemData* InItemData);
};
