// Fill out your copyright notice in the Description page of Project Settings.

#include "SPowerup.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

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

	SetReplicates(true);
}

void ASPowerUp::Interact_Implementation(APawn* InstigatorPawn)
{

}

void ASPowerUp::ShowPowerup()
{
	SetPowerupState(true);
}


void ASPowerUp::HideAndCooldownPowerup()
{
	SetPowerupState(false);

	GetWorldTimerManager().SetTimer(TimerHandle_RespawnTimer, this, &ASPowerUp::ShowPowerup, RespawnTime);
}

void ASPowerUp::SetPowerupState(bool bNewIsActive)
{
	SetActorEnableCollision(bNewIsActive);

	// Set visibility on root and all children
	RootComponent->SetVisibility(bNewIsActive, true);
}