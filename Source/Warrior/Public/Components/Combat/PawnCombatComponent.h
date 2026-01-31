// BY Zwx

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponentBase.h"
#include"GameplayTagContainer.h"
#include "PawnCombatComponent.generated.h"

class AWarriorWeaponBase;

UENUM(BlueprintType)
enum class EToggleDamageType :uint8
{
	CurrentEquippedWeapon,
	LeftHand,
	RightHand
};
/**
 * 
 */
UCLASS()
class WARRIOR_API UPawnCombatComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable,Category="WArrior|Combat")
	void RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister,
		AWarriorWeaponBase* InWeaponToRegister, 
		bool bRegisterAsEquippedWeapon = false);

	UFUNCTION(BlueprintCallable, Category = "WArrior|Combat")
	AWarriorWeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet)const;

	UPROPERTY(BlueprintReadWrite, Category = "WArrior|Combat")
	FGameplayTag CurrentEquippedWeaponTag;//

	UFUNCTION(BlueprintCallable, Category = "WArrior|Combat")
	AWarriorWeaponBase* GetCharacterCurrentEquippedWeapon() const;

	UFUNCTION(BlueprintCallable, Category = "WArrior|Combat")
	void ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType = EToggleDamageType::CurrentEquippedWeapon);

	virtual void OnHitTargetActor(AActor* HitActor);
	virtual void OnweaponPulledFromTargetActor(AActor* InteractedActor);

protected:
	virtual void ToggleCurrentEquippedWeaponCollision(bool bShouldEnable);
	virtual void ToggleBodyCollisionBoxCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType);

	TArray<AActor*> OverlappedActors;

private:
	TMap<FGameplayTag, AWarriorWeaponBase*> CharacterCarriedWeaponMap;
	
};
