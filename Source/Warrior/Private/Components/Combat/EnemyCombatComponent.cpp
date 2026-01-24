// BY Zwx


#include "Components/Combat/EnemyCombatComponent.h"

#include"WarriorDebugHelper.h"

void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (HitActor)
	{
		Debug::Print(GetOwningPawn()->GetHumanReadableName() + TEXT(" is hitting") + HitActor->GetActorNameOrLabel());
	}
}
