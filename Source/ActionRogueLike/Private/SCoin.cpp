// Fill out your copyright notice in the Description page of Project Settings.


#include "SCoin.h"
#include "SPlayerState.h"

ASCoin::ASCoin()
{
	CreditsAmount = 80;
}

void ASCoin::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn))
	{
		return;
	}

	if (ASPlayerState* PS = InstigatorPawn->GetPlayerState<ASPlayerState>())
	{
		PS->ApplyCreditValue(CreditsAmount);
		HideAndCooldownPowerup();
	}
}
