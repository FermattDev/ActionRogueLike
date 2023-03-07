// Fill out your copyright notice in the Description page of Project Settings.


#include "SThornsEffect.h"
#include <SAttributeComponent.h>

USThornsEffect::USThornsEffect()
{
	Duration = -1;
	Period = -1;
}

void USThornsEffect::StartAction_Implementation(AActor* Instigator)
{
	if (Instigator)
	{
		MyInstigator = Instigator;
		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(Instigator->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (AttributeComp)
		{
			AttributeComp->OnHealthChanged.AddDynamic(this, &USThornsEffect::OnHealthChanged);
		}
	}
}

void USThornsEffect::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);
	if (Instigator)
	{
		MyInstigator = Instigator;
		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(Instigator->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (AttributeComp)
		{
			AttributeComp->OnHealthChanged.RemoveDynamic(this, &USThornsEffect::OnHealthChanged);
		}
	}
}

void USThornsEffect::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float NewRage, float Delta)
{
	if (InstigatorActor && InstigatorActor != MyInstigator)
	{
		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(InstigatorActor->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (AttributeComp)
		{
			float ThornsAttack = FMath::DivideAndRoundNearest(Delta, 2.0f);
			AttributeComp->ApplyHealthChange(MyInstigator, ThornsAttack);
		}
	}
}
