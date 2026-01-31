// BY Zwx


#include "Components/Combat/EnemyCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "WarriorGameplayTags.h"
#include "WarriorFunctionLibrary.h"
#include "Characters/WarriorEnemyCharacter.h"
#include"Components/BoxComponent.h"

#include"WarriorDebugHelper.h"

void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (OverlappedActors.Contains(HitActor))
	{
		//Debug::Print(GetOwningPawn()->GetHumanReadableName() + TEXT(" is hitting") + HitActor->GetActorNameOrLabel());
		
		return;
	}

	OverlappedActors.AddUnique(HitActor);


	//格挡检查
	bool bIsValidBlock = false;

	const bool bIsPlayerBlocking = UWarriorFunctionLibrary::NativeDoesActorHasTag(HitActor,WarriorGameplayTags::Player_Status_Blocking);
	const bool bIsMyAttackUnblockable = UWarriorFunctionLibrary::NativeDoesActorHasTag(GetOwningPawn(), WarriorGameplayTags::Enemy_Status_Unbloackable);

	if (bIsPlayerBlocking && !bIsMyAttackUnblockable)
	{
		//检查格挡是否有效
		bIsValidBlock=UWarriorFunctionLibrary::IsValidBlock(GetOwningPawn(),HitActor);

	}

	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitActor;	

	if (bIsValidBlock)
	{
		//成功格挡
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			HitActor,
			WarriorGameplayTags::Player_Event_SuccessfulBlock,
			EventData
		);


	}
	else
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			GetOwningPawn(),
			WarriorGameplayTags::Shared_Event_MeleeHit,
			EventData
		);
	}

}

void UEnemyCombatComponent::ToggleBodyCollisionBoxCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	AWarriorEnemyCharacter* OwningEnemtCharacter = GetOwningPawn<AWarriorEnemyCharacter>();

	check(OwningEnemtCharacter);

	UBoxComponent* LeftHandcollisionBox = OwningEnemtCharacter->GetLeftHandCollisionBox();
	UBoxComponent* RightHandcollisionBox = OwningEnemtCharacter->GetRightHandCollisionBox();

	check(LeftHandcollisionBox && RightHandcollisionBox);

	switch (ToggleDamageType)
	{
	case EToggleDamageType::LeftHand:
		LeftHandcollisionBox->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;
	case EToggleDamageType::RightHand:
		RightHandcollisionBox->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;

	default:
		break;
	}

	if (!bShouldEnable)
	{
		OverlappedActors.Empty();
	}

}
