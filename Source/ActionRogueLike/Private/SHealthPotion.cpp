// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotion.h"
#include "SAttributeComponent.h"
#include "SPlayerState.h"

// Sets default values
ASHealthPotion::ASHealthPotion()
{
	HealingAmount = 100;
	CurrencyValueChange = -20;

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ASHealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(InstigatorPawn->GetComponentByClass(USAttributeComponent::StaticClass()));
	if (!AttributeComp)
	{
		return;
	}

	if (Active && !AttributeComp->HasMaxHealth())
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

		AttributeComp->ApplyHealthChange(this, HealingAmount);
		StaticMesh->SetVisibility(false);

		Active = false;

		GetWorldTimerManager().SetTimer(TimerHandle_Interact, FTimerDelegate::CreateLambda([&] { ResetPotion_TimeElapsed(); }), 10.0f, false);
	}
}

// Called when the game starts or when spawned
void ASHealthPotion::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASHealthPotion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

