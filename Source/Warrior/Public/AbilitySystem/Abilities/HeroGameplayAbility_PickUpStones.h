// BY Zwx

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/WarriorHeroGameplayAbility.h"
#include "HeroGameplayAbility_PickUpStones.generated.h"

class AWarriorStoneBase;
/**
 * 
 */
UCLASS()
class WARRIOR_API UHeroGameplayAbility_PickUpStones : public UWarriorHeroGameplayAbility
{
	GENERATED_BODY()
	
protected:
	//Begin UGameplayAbility interface
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData)override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)override;
	//End UGameplayAbility interface

	UFUNCTION(BlueprintCallable)
	void CollectStones();

	UFUNCTION(BlueprintCallable)
	void ConsumeStones();

private:
	UPROPERTY(EditAnywhere)
	float BoxTraceDistance = 50.f;

	UPROPERTY(EditAnywhere)
	FVector TraceBoxSize = FVector(100.f);

	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<	EObjectTypeQuery> > StoneTraceChannel;

	UPROPERTY(EditAnywhere)
	bool bDrawDebugBox = false;

	UPROPERTY()
	TArray<AWarriorStoneBase*> CollectedStones;
};
