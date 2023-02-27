// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"

int ASPlayerState::GetCreditAmount()
{
	return CreditsAmount;
}

bool ASPlayerState::ApplyCreditValue(int delta)
{
	int result = CreditsAmount + delta;
	if (result < 0)
	{
		return false;
	}

	CreditsAmount = result;

	UE_LOG(LogTemp, Log, TEXT("Current credits amount: %i"), CreditsAmount);

	return true;
}
