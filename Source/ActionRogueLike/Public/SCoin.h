// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPowerUp.h"
#include "SCoin.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASCoin : public ASPowerUp
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ASCoin();

protected:

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
};
