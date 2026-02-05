// BY Zwx

#pragma once

#include "CoreMinimal.h"
#include "Items/PickUps/WarriorPickupBase.h"
#include "WarriorStoneBase.generated.h"

class UWarriorAbilitySystemComponent;
class UGameplayEffect;
/**
 * 
 */
UCLASS()
class WARRIOR_API AWarriorStoneBase : public AWarriorPickupBase
{
	GENERATED_BODY()

public:
	void Consume(UWarriorAbilitySystemComponent* AbilitySystemComponent,int32 ApplyLevel);


	
protected:
	virtual void OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)override;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName="On Stone Consumed"))
	void BP_OnStoneConsumed();


	UPROPERTY(EDitDefaultsOnly)
	TSubclassOf<UGameplayEffect>StoneGameplayEffectClass;
};
