// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	MaxHealth = 100;
	Health = MaxHealth;
}

bool USAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	if(!GetOwner()->CanBeDamaged())
	{
		return false;
	}

	Health += Delta;
	Health = FMath::Clamp(Health, 0, MaxHealth);

	OnHealthChanged.Broadcast(InstigatorActor, this, Health, MaxHealth, Delta);

	UE_LOG(LogTemp, Warning, TEXT("Explode caused by: %f"), Health);

	return true;
}

bool USAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

float USAttributeComponent::GetCurrentHealth()
{
	return Health;
}

bool USAttributeComponent::HasMaxHealth() const
{
	return Health >= MaxHealth;
}

bool USAttributeComponent::Kill(AActor* Instigator)
{
	return ApplyHealthChange(Instigator, -MaxHealth);
}

USAttributeComponent* USAttributeComponent::GetAttributes(AActor* FromActor)
{
	if (FromActor)
	{
		return Cast<USAttributeComponent>(FromActor->GetComponentByClass(USAttributeComponent::StaticClass()));
	}

	return nullptr;
}

bool USAttributeComponent::IsActorAlive(AActor* Actor)
{
	USAttributeComponent* AttributeComp = GetAttributes(Actor);
	if (AttributeComp)
	{
		return AttributeComp->IsAlive();
	}

	return false;
}
