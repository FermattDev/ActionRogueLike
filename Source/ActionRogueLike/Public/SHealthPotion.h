// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPowerUp.h"
#include "SHealthPotion.generated.h"

class UStaticMeshComponent;

UCLASS()
class ACTIONROGUELIKE_API ASHealthPotion : public ASPowerUp
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASHealthPotion();

protected:

	UPROPERTY(EditAnywhere, Category = "HealthPotion")
	int32 CreditCost;

public:

	void Interact_Implementation(APawn* InstigatorPawn) override;

	FText GetInteractText_Implementation(APawn* InstigatorPawn) override;

};
