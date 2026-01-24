// BY Zwx

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/DataAsset_StartUpdateBase.h"
#include "WarriorTypes/WarriorStructTypes.h"
#include "DataAsset_HeroStartUpdate.generated.h"



/**
 * 
 */
UCLASS()
class WARRIOR_API UDataAsset_HeroStartUpdate : public UDataAsset_StartUpdateBase
{
	GENERATED_BODY()

public:
	virtual void GiveToWarriorAbilitySystemComponent(UWarriorAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1)override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData",meta=(TitleProperty="InputTag"))
	TArray<FWarriorHeroAbilitySet> HeroStartUpAbilitySets;
};
