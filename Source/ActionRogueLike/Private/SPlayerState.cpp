// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"
#include <Net/UnrealNetwork.h>

void ASPlayerState::MulticastCreditsChanged_Implementation(AActor* CreditsInstigator, float NewCredits, float Delta)
{
	OnCreditsChanged.Broadcast(this, NewCredits, Delta);
}

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

	OnCreditsChanged.Broadcast(this, CreditsAmount, delta);

	UE_LOG(LogTemp, Log, TEXT("Current credits amount: %i"), CreditsAmount);

	return true;
}

void ASPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASPlayerState, CreditsAmount);
}