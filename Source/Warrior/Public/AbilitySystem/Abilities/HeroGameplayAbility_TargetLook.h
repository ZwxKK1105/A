// BY Zwx

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/WarriorHeroGameplayAbility.h"
#include "HeroGameplayAbility_TargetLook.generated.h"


class UWarriorWidgetBase;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class WARRIOR_API UHeroGameplayAbility_TargetLook : public UWarriorHeroGameplayAbility
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
	void OnTargetLockTick(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	void SwitchTarget(const FGameplayTag& InSwitchDirectionTag);


private:
	void TryLockOnTarget();

	void GetAvailableActorsToLock();

	AActor* GetNearestTargetFromAvailableActors(const TArray<AActor*>& InAvailableActors);
	void GetAvailableActorsAroundTarget(TArray<AActor*>& OutActorsOnLeft, TArray<AActor*>& OutActorsOnRight);


	void DrawTargetLockWidget();

	void InitTargetLockMovement();
	void InitTargetLockMappingContext();


	void SetTargetLockWidgetTargetPosition();

	void CancelTargetlockAbility();

	void ClearUp();

	void ResetTargetLockMovement();
	void ResetTargetLockMappingContext();

	UPROPERTY(EditDefaultsOnly, Category = "TargetLook")
	float BoxTraceDistance = 5000.f;

	UPROPERTY(EditDefaultsOnly, Category = "TargetLook")
	FVector BraceBoxSize = FVector(5000.f,5000.f,300.f);

	UPROPERTY(EditDefaultsOnly, Category = "TargetLook")
	TArray<TEnumAsByte<	EObjectTypeQuery> > BoxTraceChannel;

	UPROPERTY(EditDefaultsOnly, Category = "TargetLook")
	bool bShowPersistentDebugShape = false;

	UPROPERTY(EditDefaultsOnly, Category = "TargetLook")
	TSubclassOf<UWarriorWidgetBase> TargetLockWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "TargetLook")
	float TargetLockRotationInterpSpeed = 5.f;

	UPROPERTY(EditDefaultsOnly, Category = "TargetLook")
	float TargetLockMaxWalkSpeed = 150.f;

	UPROPERTY(EditDefaultsOnly, Category = "TargetLook")
	UInputMappingContext* TargetLockMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "TargetLook")
	float TargetLocketCameraOffestDistance = 20.f;

	UPROPERTY()
	TArray<AActor*> AvailableActorsToLock;

	UPROPERTY()
	AActor* CurrentLockedActor;

	UPROPERTY()
	UWarriorWidgetBase* DrawnTargetLockWidget;

	UPROPERTY()
	FVector2D TargetLockWidgetSize = FVector2D::ZeroVector;

	UPROPERTY()
	float CachedDefaultMaxWalkSpeed = 0.f;

};
