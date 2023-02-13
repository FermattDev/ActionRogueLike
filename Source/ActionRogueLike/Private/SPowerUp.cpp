// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerUp.h"

// Sets default values
ASPowerUp::ASPowerUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;
}

void ASPowerUp::ResetPotion_TimeElapsed()
{
	Active = true;
	StaticMesh->SetVisibility(true);
}

void ASPowerUp::Interact_Implementation(APawn* InstigatorPawn)
{
}

// Called when the game starts or when spawned
void ASPowerUp::BeginPlay()
{
	Super::BeginPlay();

	Active = true;
	StaticMesh->SetVisibility(true);
}

// Called every frame
void ASPowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

