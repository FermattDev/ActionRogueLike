// Fill out your copyright notice in the Description page of Project Settings.


#include "SCoin.h"
#include "SPlayerState.h"

ASCoin::ASCoin()
{
	CurrencyValueChange = 20;
}

void ASCoin::Interact_Implementation(APawn* InstigatorPawn)
{
	ASPlayerState* state = InstigatorPawn->GetPlayerState<ASPlayerState>();

	if (state == nullptr)
	{
		return;
	}
	if (!state->ApplyCreditValue(CurrencyValueChange))
	{
		return;
	}

	Destroy();
}
