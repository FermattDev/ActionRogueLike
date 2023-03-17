// Fill out your copyright notice in the Description page of Project Settings.

#include "SPowerup.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include <Net/UnrealNetwork.h>

// Sets default values
ASPowerUp::ASPowerUp()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	// Disable collision, instead we use SphereComp to handle interaction queries
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetupAttachment(RootComponent);

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Powerup");
	SphereComp->SetupAttachment(RootComponent);

	RespawnTime = 10.0f;

	bReplicates = true;
}

void ASPowerUp::OnRep_PowerUpTriggered()
{
	if (bPowerUpTriggered)
	{
		SetPowerupState(false);
		return;
	}
	SetPowerupState(true);
}

void ASPowerUp::Interact_Implementation(APawn* InstigatorPawn)
{

}

FText ASPowerUp::GetInteractText_Implementation(APawn* InstigatorPawn)
{
	return FText::GetEmpty();
}

void ASPowerUp::ShowPowerup()
{
	bPowerUpTriggered = false;

	SetPowerupState(true);
}


void ASPowerUp::HideAndCooldownPowerup()
{
	bPowerUpTriggered = true;

	SetPowerupState(false);

	GetWorldTimerManager().SetTimer(TimerHandle_RespawnTimer, this, &ASPowerUp::ShowPowerup, RespawnTime);
}

void ASPowerUp::SetPowerupState(bool bNewIsActive)
{
	SetActorEnableCollision(bNewIsActive);

	// Set visibility on root and all children
	RootComponent->SetVisibility(bNewIsActive, true);
}

void ASPowerUp::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASPowerUp, bPowerUpTriggered);
}