// BY Zwx


#include "AbilitySystem/Abilities/WarriorHeroGameplayAbility.h"
#include "Characters/WarriorHeroCharacter.h"
#include "Controllers/WarriorHeroController.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "WarriorGameplayTags.h"


AWarriorHeroCharacter* UWarriorHeroGameplayAbility::GetHeroCharacterFromActorInfo()
{
    if (!CachedAWarriorHeroCharacter.IsValid())
    {
        CachedAWarriorHeroCharacter = Cast<AWarriorHeroCharacter>(CurrentActorInfo->AvatarActor);
    }

    return CachedAWarriorHeroCharacter.IsValid() ? CachedAWarriorHeroCharacter.Get() : nullptr;
}

AWarriorHeroController* UWarriorHeroGameplayAbility::GetHeroControllerFromActorInfo()
{
    if (!CachedAWarriorHeroController.IsValid())
    {
        CachedAWarriorHeroController=Cast<AWarriorHeroController>(CurrentActorInfo->PlayerController);
    }

    return CachedAWarriorHeroController.IsValid() ? CachedAWarriorHeroController.Get() : nullptr;
}

UHeroCombatComponent* UWarriorHeroGameplayAbility::GetHeroCombatComponentFromActorInfo()
{

    return GetHeroCharacterFromActorInfo()->GetHeroCombatComponent();
}

UHeroUIComponent* UWarriorHeroGameplayAbility::GetHeroUIComponentFromActorInfo()
{
	return GetHeroCharacterFromActorInfo()->GetHeroUIComponent();
}



FGameplayEffectSpecHandle UWarriorHeroGameplayAbility::MakeHeroDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass,
    float InWeaponBaseDamage, FGameplayTag InCurrentAttacktypeTag, int32 InUsedComboCount)
{
    check(EffectClass);

    FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponentFromActorInfo()->MakeEffectContext();
    ContextHandle.SetAbility(this);
    ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
    ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());


    FGameplayEffectSpecHandle EffectSpecHandle =GetAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
        EffectClass,
        GetAbilityLevel(),
        ContextHandle
    );

    EffectSpecHandle.Data->SetSetByCallerMagnitude(
        WarriorGameplayTags::Shared_SetByCaller_BaseDamage,
        InWeaponBaseDamage
    );

    if (InCurrentAttacktypeTag.IsValid())
    {
        EffectSpecHandle.Data->SetSetByCallerMagnitude(InCurrentAttacktypeTag, InUsedComboCount);
    }

    return EffectSpecHandle;
}

bool UWarriorHeroGameplayAbility::GetAbilityRemainingCooldownByTag(FGameplayTag InCooldownTag, float& TotalCooldownTime, float& RemainingCooldownTime)
{
    check(InCooldownTag.IsValid());

    FGameplayEffectQuery CooldownQuery = FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(InCooldownTag.GetGameplayTagParents());

	TArray<TPair<float,float>> TimeRemainingAndDuration = GetAbilitySystemComponentFromActorInfo()->GetActiveEffectsTimeRemainingAndDuration(CooldownQuery);

    if (!TimeRemainingAndDuration.IsEmpty())
    {
		RemainingCooldownTime = TimeRemainingAndDuration[0].Key;
		TotalCooldownTime = TimeRemainingAndDuration[0].Value;
		
    }

	return RemainingCooldownTime > 0.f;
}
