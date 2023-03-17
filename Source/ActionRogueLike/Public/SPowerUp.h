// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGameplayInterface.h"
#include "SPowerup.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class USceneComponent;

UCLASS()
class ACTIONROGUELIKE_API ASPowerUp : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPowerUp();

protected:

	UPROPERTY(ReplicatedUsing = "OnRep_PowerUpTriggered", BlueprintReadOnly)
	bool bPowerUpTriggered;

	UFUNCTION()
	void OnRep_PowerUpTriggered();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, Category = "Powerup")
	float RespawnTime;

	FTimerHandle TimerHandle_RespawnTimer;

	UFUNCTION()
	void ShowPowerup();

	void HideAndCooldownPowerup();

	void SetPowerupState(bool bNewIsActive);

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

public:	

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

	FText GetInteractText_Implementation(APawn* InstigatorPawn);

};
