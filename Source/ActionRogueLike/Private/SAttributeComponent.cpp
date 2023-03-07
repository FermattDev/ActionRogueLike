// Fill out your copyright notice in the Description page of Project Settings.

#include "SAttributeComponent.h"
#include <AI/SGameModeBase.h>
#include <Net/UnrealNetwork.h>

static TAutoConsoleVariable<float> CVarDamageMultiplier(TEXT("su.DamageMultiplier"), 1.0f, TEXT("Global damage modifier for attribute component."), ECVF_Cheat);

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	MaxHealth = 100;
	Health = MaxHealth;

	SetIsReplicatedByDefault(true);
}

void USAttributeComponent::MulticastHealthChanged_Implementation(AActor* Instigator, float NewHealth, float NewRage, float Delta)
{
	OnHealthChanged.Broadcast(Instigator, this, NewHealth, NewRage, Delta);
}

bool USAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	if(!GetOwner()->CanBeDamaged() && Delta < 0.0f || !IsAlive())
	{
		return false;
	}

	if (Delta < 0.0f)
	{
		float DamageMultiplier = CVarDamageMultiplier.GetValueOnGameThread();

		Delta *= DamageMultiplier;

		Rage += FMath::Abs(Delta);
		Rage = FMath::Clamp(Rage, 0, MaxRage);
	}
	else if (Delta == 0.0f)
	{
		return false;
	}

	Health += Delta;
	Health = FMath::Clamp(Health, 0, MaxHealth);

	//OnHealthChanged.Broadcast(InstigatorActor, this, Health, MaxHealth, Delta);

	MulticastHealthChanged(InstigatorActor, Health, Rage, Delta);

	if (Delta < 0.0f && Health == 0.0f)
	{
		ASGameModeBase* GM = GetWorld()->GetAuthGameMode<ASGameModeBase>();
		if (GM)
		{
			GM->OnActorKilled(GetOwner(), InstigatorActor);
		}
	}

	return true;
}

bool USAttributeComponent::CheckRageCost(AActor* InstigatorActor, float Delta)
{
	if (Delta <= 0)
	{
		return true;
	}

	float NewRage = Rage - Delta;
	if (NewRage < 0)
	{
		return false;
	}
	Rage = NewRage;

	MulticastHealthChanged(InstigatorActor, Health, Rage, Delta);

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

float USAttributeComponent::GetMaxHealth()
{
	return MaxHealth;
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

void USAttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USAttributeComponent, Health);
	DOREPLIFETIME(USAttributeComponent, MaxHealth);

	//DOREPLIFETIME_CONDITION(USAttributeComponent, MaxHealth, COND_OwnerOnly)
}