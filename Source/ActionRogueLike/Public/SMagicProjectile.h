// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SProjectile.h"
#include "SMagicProjectile.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ASMagicProjectile : public ASProjectile
{
	GENERATED_BODY()
	
private:
	FTimerHandle TimerHandle_Destroy;

public:	
	UPROPERTY(EditAnywhere)
	UParticleSystem* DestroyEffect;

	UPROPERTY(EditAnywhere)
	UAudioComponent* FlightAudio;

	UPROPERTY(EditAnywhere)
	USoundBase* DestroySound;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TSubclassOf<UCameraShakeBase> ImpactStrike;

	UPROPERTY(EditAnywhere)
	float Damage;

	// Sets default values for this actor's properties
	ASMagicProjectile();

	// Called when the game starts or when spawned
	virtual void PostInitializeComponents() override;

protected:
	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	void DestroyProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
