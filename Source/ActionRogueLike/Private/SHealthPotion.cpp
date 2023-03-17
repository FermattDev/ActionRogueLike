// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotion.h"
#include "SAttributeComponent.h"
#include "SPlayerState.h"

#define LOCTEXT_NAMESPACE "InteractableActors"

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

FText ASHealthPotion::GetInteractText_Implementation(APawn* InstigatorPawn)
{
	USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(InstigatorPawn);
	if (AttributeComp && AttributeComp->HasMaxHealth())
	{
		return LOCTEXT("HealthPotion_FullHealthWarning", "Already at full health.");
	}

	return FText::Format(LOCTEXT("HealthPotion_InteractMessage", "Cost {0} Credits. Restores health to Max"), CreditCost);
}

#undef LOCTEXT_NAMESPACE