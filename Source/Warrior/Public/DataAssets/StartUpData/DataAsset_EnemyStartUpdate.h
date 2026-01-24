// BY Zwx

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/DataAsset_StartUpdateBase.h"
#include "DataAsset_EnemyStartUpdate.generated.h"


class UWarriorEnemyGameplayAbility;
/**
 * 
 */
UCLASS()
class WARRIOR_API UDataAsset_EnemyStartUpdate : public UDataAsset_StartUpdateBase
{
	GENERATED_BODY()
	
public:
	virtual void GiveToWarriorAbilitySystemComponent(UWarriorAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1)override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UWarriorEnemyGameplayAbility>>EnemyCombatAbilities;

};
