// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASPlayerState : public APlayerState
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, Category = "Currency")
	int CreditsAmount;

public:
	UFUNCTION(BlueprintCallable)
	int GetCreditAmount();

	UFUNCTION(BlueprintCallable)
	bool ApplyCreditValue(int delta);
};
