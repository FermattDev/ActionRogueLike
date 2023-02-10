// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SProjectile.h"
#include "SDashProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASDashProjectile : public ASProjectile
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASDashProjectile();

protected:
	FTimerHandle TimerHandle_Teleport;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* TeleportEffectComp;

	UFUNCTION()
	void TriggerTeleportTime(UParticleSystemComponent* PSystem);

	UFUNCTION()
	void TriggerTeleportOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	void TeleportPlayer();

	// Called when the game starts or when spawned
	virtual void PostInitializeComponents() override;

private:
	bool TeleportTriggered = false;
};
