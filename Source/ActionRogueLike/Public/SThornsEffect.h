// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SActionEffect.h"
#include "SThornsEffect.generated.h"

class USAttributeComponent;

UCLASS()
class ACTIONROGUELIKE_API USThornsEffect : public USActionEffect
{
	GENERATED_BODY()
	
public:

	USThornsEffect();

	void StartAction_Implementation(AActor* Instigator) override;
	void StopAction_Implementation(AActor* Instigator) override;

protected:

	AActor* MyInstigator;

	void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float NewRage, float Delta);
};
