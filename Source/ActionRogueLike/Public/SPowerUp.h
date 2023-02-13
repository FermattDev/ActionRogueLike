// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGameplayInterface.h"
#include "SPowerUp.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ASPowerUp : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPowerUp();

protected:

	bool Active;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMesh;

	FTimerHandle TimerHandle_Interact;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ResetPotion_TimeElapsed();

	virtual void Interact_Implementation(APawn* InstigatorPawn);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
