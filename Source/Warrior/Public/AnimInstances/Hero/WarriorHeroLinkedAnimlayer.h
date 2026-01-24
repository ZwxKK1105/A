// BY Zwx

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/WarriorBaseAnimInstance.h"
#include "WarriorHeroLinkedAnimlayer.generated.h"

class UWarriorHeroEnumAnimInstance;
/**
 * 
 */
UCLASS()
class WARRIOR_API UWarriorHeroLinkedAnimlayer : public UWarriorBaseAnimInstance
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure,meta=(BlueprintThreadSafe))
	UWarriorHeroEnumAnimInstance* GetHeroAnimInstance() const;
};
