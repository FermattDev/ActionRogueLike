// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPowerUp.h"
#include "SActionGrant.generated.h"

class USAction;

UCLASS()
class ACTIONROGUELIKE_API ASActionGrant : public ASPowerUp
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Category = "Actions")
	TSubclassOf<USAction> ActionGranted;

public:
	void Interact_Implementation(APawn* InstigatorPawn) override;
};
