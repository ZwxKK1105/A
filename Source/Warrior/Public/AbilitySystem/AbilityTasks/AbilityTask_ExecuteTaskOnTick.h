// BY Zwx

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_ExecuteTaskOnTick.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbilityTaskTickDelegate, float, DeltaTime);

/**
 * 
 */
UCLASS()
class WARRIOR_API UAbilityTask_ExecuteTaskOnTick : public UAbilityTask
{
	GENERATED_BODY()
	
public:
	UAbilityTask_ExecuteTaskOnTick();


	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks",meta=(HidePin="OwningAbility",DefaultToSelf="OwningAbility",BlueprintInternalUseOnly="true"))
	static UAbilityTask_ExecuteTaskOnTick* ExecuteTaskOnTick(UGameplayAbility* OwningAbility);

	//Being UGameplayTask interface
	virtual void TickTask(float DeltaTime) override;
	//End UGameplayTask interface

	

	UPROPERTY(BlueprintAssignable)
	FOnAbilityTaskTickDelegate OnAbilityTaskTick;

};
