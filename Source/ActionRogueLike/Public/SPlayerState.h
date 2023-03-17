// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPlayerState.generated.h"

class USSaveGame;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCreditsChanged, ASPlayerState*, PlayerState, int32, NewCredits, int32, Delta);

UCLASS()
class ACTIONROGUELIKE_API ASPlayerState : public APlayerState
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(Replicated, VisibleAnywhere, Category = "Currency")
	int CreditsAmount;

public:
	UFUNCTION(NetMulticast, Reliable)
	void MulticastCreditsChanged(AActor* CreditsInstigator, float NewCredits, float Delta);

	UFUNCTION(BlueprintCallable)
	int GetCreditAmount();

	UFUNCTION(BlueprintCallable)
	bool ApplyCreditValue(int delta);

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnCreditsChanged OnCreditsChanged;

	UFUNCTION(BlueprintNativeEvent)
	void SavePlayerState(USSaveGame* SaveObject);

	UFUNCTION(BlueprintNativeEvent)
	void LoadPlayerState(USSaveGame* SaveObject);
};
