// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "SPowerUp.h"
#include "Engine/DataTable.h"
#include "SGameModeBase.generated.h"

class UEnvQuery;
class UEnvQueryInstanceBlueprintWrapper;
class UCurveFloat;
class USSaveGame;
class UDataTable;
class USMonsterData;

USTRUCT(BlueprintType)
struct FMonsterInfoRow : public FTableRowBase
{
	GENERATED_BODY()

public:

	FMonsterInfoRow()
	{
		Weight = 1.0f;
		SpawnCost = 5.0f;
		KillReward = 20.0f;
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FPrimaryAssetId MonsterId;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Weight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SpawnCost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float KillReward;
};

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:

	FString SlotName;

	UPROPERTY()
	USSaveGame* CurrentSaveGame;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UDataTable* MonsterTable;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TSubclassOf<ASPowerUp> CoinPowerUp;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TSubclassOf<ASPowerUp> PotionPowerUp;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UEnvQuery* SpawnBotQuery;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UEnvQuery* SpawnPowerUpQuery;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UCurveFloat* DifficultyCurve;

	FTimerHandle TimerHandle_SpawnBots;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float SpawnTimerInterval;

	UPROPERTY(EditDefaultsOnly, Category = "Currency", Meta=(ClampMin = "0"))
	float MinionKilledCurrencyReward;

	UPROPERTY(EditDefaultsOnly, Category = "Power Ups", Meta = (ClampMin = "0"))
	int CoinSpawnAmount;

	UPROPERTY(EditDefaultsOnly, Category = "Power Ups", Meta = (ClampMin = "0"))
	int PotionSpawnAmount;
	
	UFUNCTION()
	void SpawnPowerUps();

	UFUNCTION()
	void SpawnBotTimerElapsed();

	UFUNCTION()
	void OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	void OnMonsterLoaded(FPrimaryAssetId LoadedId, FVector SpawnLocation);

	UFUNCTION()
	void OnCoinQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	UFUNCTION()
	void OnPotionQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	UFUNCTION()
	void RespawnPlayerElapsed(AController* Controller);

public:
	ASGameModeBase();

	void InitGame(const FString& MapNAme, const FString& Options, FString& ErrorMessage) override;

	virtual void StartPlay() override;

	void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

	UFUNCTION(Exec)
	void KillAll();

	virtual void OnActorKilled(AActor* VictimActor, AActor* Killer);

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void WriteSaveGame();

	void LoadSaveGame();
};
