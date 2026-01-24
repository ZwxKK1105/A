// BY Zwx


#include "AnimInstances/Hero/WarriorHeroLinkedAnimlayer.h"
#include "AnimInstances/Hero/WarriorHeroEnumAnimInstance.h"

UWarriorHeroEnumAnimInstance* UWarriorHeroLinkedAnimlayer::GetHeroAnimInstance() const
{
    return Cast<UWarriorHeroEnumAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
