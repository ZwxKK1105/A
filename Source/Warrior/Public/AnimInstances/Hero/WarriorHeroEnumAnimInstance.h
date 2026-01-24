// BY Zwx

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/WarriorCharacterAnimInstance.h"
#include "WarriorHeroEnumAnimInstance.generated.h"

class AWarriorHeroCharacter;
/**
 * 
 */
UCLASS()
class WARRIOR_API UWarriorHeroEnumAnimInstance : public UWarriorCharacterAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation()override;

	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds)override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData|Refrences")
	AWarriorHeroCharacter* OwningHeroCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData|Locomotiondata")
	bool bShouldEnterRelaxState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimData|Locomotiondata")
	float EnterRelaxStateThreshold = 5.f;

	float IdleElpasedTime;
};
