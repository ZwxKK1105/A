// BY Zwx


#include "GameModes/WarriorSurvialGameMode.h"
#include "Engine/AssetManager.h"
#include "Characters/WarriorEnemyCharacter.h"
#include"Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"
#include "NavigationSystem.h"


#include"WarriorDebugHelper.h"

void AWarriorSurvialGameMode::BeginPlay()
{
	Super::BeginPlay();

	checkf(EnemyWaveSpawnerDataTable, TEXT("Forgot Assign a valid Dara Table"));

	SetCurrentSurvialGameModeState(EWarriorSurvialGameModeState::WaitSpawnNewWave);

	TotalWavesToSpawn=EnemyWaveSpawnerDataTable->GetRowNames().Num();

	PreLoadNextWaveEnemies();
}

void AWarriorSurvialGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (CurrentSurvialGameModeState == EWarriorSurvialGameModeState::WaitSpawnNewWave)
	{
		TimePossedSinceStart += DeltaSeconds;

		if (TimePossedSinceStart >= SpawnNewWaveWaitTime)
		{
			TimePossedSinceStart = 0;

			SetCurrentSurvialGameModeState(EWarriorSurvialGameModeState::SpawningNewWave);
		}
	}

	if (CurrentSurvialGameModeState == EWarriorSurvialGameModeState::SpawningNewWave)
	{
		TimePossedSinceStart += DeltaSeconds;

		if (TimePossedSinceStart >= SpawnEnemiesDelayTime)
		{
			CurrentSpawnedEnemiesCounter += TrySpawnWaveEnemies();
			//生成新敌人
			TimePossedSinceStart = 0.f;

			SetCurrentSurvialGameModeState(EWarriorSurvialGameModeState::InProgress);

		}
	}

	if (CurrentSurvialGameModeState == EWarriorSurvialGameModeState::WaveCompleted)
	{
		TimePossedSinceStart += DeltaSeconds;

		if (TimePossedSinceStart >= WaveCompletedWaitTime)
		{
			TimePossedSinceStart = 0.f;

			CurrentWaveCount++;

			if (HasFinishedAllWaves())
			{
				SetCurrentSurvialGameModeState(EWarriorSurvialGameModeState::AllWavesDone);
			}
			else
			{
				SetCurrentSurvialGameModeState(EWarriorSurvialGameModeState::WaitSpawnNewWave);

				PreLoadNextWaveEnemies();
			}
		}

	}


}

void AWarriorSurvialGameMode::SetCurrentSurvialGameModeState(EWarriorSurvialGameModeState InState)
{
	CurrentSurvialGameModeState = InState;
	OnSurvialGameModeStateChanged.Broadcast(CurrentSurvialGameModeState);
}

bool AWarriorSurvialGameMode::HasFinishedAllWaves() const
{
	return CurrentWaveCount > TotalWavesToSpawn;
}

void AWarriorSurvialGameMode::PreLoadNextWaveEnemies()
{
	if (HasFinishedAllWaves())
	{
		return;
	}
	PreLoadedEnemyClassMap.Empty();


	for (const FWarriorEnemyWaveSpawnerInfo& SpawnerInfo : GetCurrentWaveSpawnerTableRow()->EnemyWaveSpawnerDedinitions)
	{
		if (SpawnerInfo.SoftEnemyClassToSpawn.IsNull())continue;

		UAssetManager::GetStreamableManager().RequestAsyncLoad(
			SpawnerInfo.SoftEnemyClassToSpawn.ToSoftObjectPath(), 
			FStreamableDelegate::CreateLambda(
				[SpawnerInfo,this]()
				{
					if (UClass* LoadedEnemyClass = SpawnerInfo.SoftEnemyClassToSpawn.Get())
					{
						PreLoadedEnemyClassMap.Emplace(SpawnerInfo.SoftEnemyClassToSpawn, LoadedEnemyClass);

						//Debug::Print(LoadedEnemyClass->GetName() + TEXT("is loading"));
					}
				}
			)
		);
	}

}

FWarriorEnemyWaveSpawnerTableRow* AWarriorSurvialGameMode::GetCurrentWaveSpawnerTableRow() const
{
	const FName RowName = FName(TEXT("Wave")+FString::FromInt(CurrentWaveCount));

	FWarriorEnemyWaveSpawnerTableRow* FoundRow = EnemyWaveSpawnerDataTable->FindRow<FWarriorEnemyWaveSpawnerTableRow>(RowName, FString());

	checkf(FoundRow, TEXT("Could not find a valid row under the name %s in the data table"), *RowName.ToString());

	return FoundRow;
}

int32 AWarriorSurvialGameMode::TrySpawnWaveEnemies()
{
	if (TargetPointsArray.IsEmpty())
	{
		UGameplayStatics::GetAllActorsOfClass(this, ATargetPoint::StaticClass(), TargetPointsArray);
	}

	checkf(!TargetPointsArray.IsEmpty(), TEXT("No Valid Target point found this level :%s for spawning enemies"), *GetWorld()->GetName());

	uint32 EnemiesSpawnedThisTime = 0;

	FActorSpawnParameters SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	//遍历生成敌人
	for (const FWarriorEnemyWaveSpawnerInfo& SpawnerInfo : GetCurrentWaveSpawnerTableRow()->EnemyWaveSpawnerDedinitions)
	{
		if (SpawnerInfo.SoftEnemyClassToSpawn.IsNull())continue;

		const int32 NumToSpawn = FMath::RandRange(SpawnerInfo.MinPerSpawnCount, SpawnerInfo.MaxPerSpawnCount);

		UClass* LoadedEnemyClass = PreLoadedEnemyClassMap.FindChecked(SpawnerInfo.SoftEnemyClassToSpawn);

		for (int i = 0; i < NumToSpawn; i++)
		{
			const int32 RandomTargetPointIndex = FMath::RandRange(0, TargetPointsArray.Num() - 1);
			const FVector SpawnOrigin = TargetPointsArray[RandomTargetPointIndex]->GetActorLocation();
			const FRotator SpawnRotation = TargetPointsArray[RandomTargetPointIndex]->GetActorForwardVector().ToOrientationRotator();

			FVector RandomLocation;
			UNavigationSystemV1::K2_GetRandomLocationInNavigableRadius(this, SpawnOrigin, RandomLocation,400.f);

			RandomLocation += FVector(0.f, 0.f, 150.f);


			AWarriorEnemyCharacter* SpawnedEnemy = GetWorld()->SpawnActor<AWarriorEnemyCharacter>(LoadedEnemyClass, RandomLocation, SpawnRotation, SpawnParam);
			if (SpawnedEnemy)
			{
				SpawnedEnemy->OnDestroyed.AddDynamic(this, &ThisClass::OnEnemyDestroy);

				EnemiesSpawnedThisTime++;
				TotalSpawnedEnemiesThisWaveCounter++;
			}

			if (!ShouldKeepSpawnEnemies())
			{
				return EnemiesSpawnedThisTime;
			}


		}

	}

	return EnemiesSpawnedThisTime;
}

bool AWarriorSurvialGameMode::ShouldKeepSpawnEnemies() const
{
	return TotalSpawnedEnemiesThisWaveCounter < GetCurrentWaveSpawnerTableRow()->TotalEnemyToSpawnThisWave;
}

void AWarriorSurvialGameMode::OnEnemyDestroy(AActor* DeadActor)
{
	CurrentSpawnedEnemiesCounter--;

	Debug::Print(FString::Printf(TEXT("CurrentSpawnedrnrmiesCounter:%i,TotalSpawnedEnemiesThisWaveCounter:%i"), CurrentSpawnedEnemiesCounter, TotalSpawnedEnemiesThisWaveCounter));

	if (ShouldKeepSpawnEnemies())
	{
		CurrentSpawnedEnemiesCounter +=TrySpawnWaveEnemies();
	}
	else if (CurrentSpawnedEnemiesCounter == 0)
	{
		//一波结束
		TotalSpawnedEnemiesThisWaveCounter = 0;
		CurrentSpawnedEnemiesCounter = 0;

		SetCurrentSurvialGameModeState(EWarriorSurvialGameModeState::WaveCompleted);
	}

}

void AWarriorSurvialGameMode::RegisterSpawnedEnemies(const TArray<AWarriorEnemyCharacter*>& InEnemiesToRegister)
{
	for (AWarriorEnemyCharacter* SpawnedEnemy : InEnemiesToRegister)
	{
		CurrentSpawnedEnemiesCounter++;

		SpawnedEnemy->OnDestroyed.AddDynamic(this, &ThisClass::OnEnemyDestroy);
	}
}



