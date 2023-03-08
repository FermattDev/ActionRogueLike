// Fill out your copyright notice in the Description page of Project Settings.


#include "SActionGrant.h"
#include <SActionComponent.h>

void ASActionGrant::Interact_Implementation(APawn* InstigatorPawn)
{
	if (ensure(InstigatorPawn))
	{
		USActionComponent* ActionComp = Cast<USActionComponent>(InstigatorPawn->GetComponentByClass(USActionComponent::StaticClass()));

		if (!ActionComp->IsActionAdded(ActionGranted))
		{
			ActionComp->AddAction(InstigatorPawn, ActionGranted);
		}
	}
}

