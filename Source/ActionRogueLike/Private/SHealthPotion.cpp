// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotion.h"
#include "SAttributeComponent.h"
#include "SPlayerState.h"

ASHealthPotion::ASHealthPotion()
{
	CreditCost = 50;
}

void ASHealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn))
	{
		return;
	}

	USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(InstigatorPawn);
	// Check if not already at max health
	if (ensure(AttributeComp) && !AttributeComp->HasMaxHealth())
	{
		if (ASPlayerState* PS = InstigatorPawn->GetPlayerState<ASPlayerState>())
		{
			if (PS->ApplyCreditValue(-CreditCost) && AttributeComp->ApplyHealthChange(this, 999))
			{
				// Only activate if healed successfully
				HideAndCooldownPowerup();
			}
		}
	}
}
