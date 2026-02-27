// BY Zwx

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include"WarriorTypes/WarriorEnumTypes.h"
#include "WarrriorSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class WARRIOR_API UWarrriorSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
	EWarriorGameDifficulty SavedCurrentGameDifficulty;


};
