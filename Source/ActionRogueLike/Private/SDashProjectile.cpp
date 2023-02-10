// Fill out your copyright notice in the Description page of Project Settings.

#include "SDashProjectile.h"

ASDashProjectile::ASDashProjectile()
{
	TeleportEffectComp = CreateDefaultSubobject<UParticleSystemComponent>("TeleportEffectComp");
	TeleportEffectComp->SetupAttachment(SphereComp);
	TeleportEffectComp->bAutoActivate = false;
}

void ASDashProjectile::TriggerTeleportTime(UParticleSystemComponent* PSystem)
{
	if (TeleportTriggered)
	{
		return;
	}
	TeleportTriggered = true;
	TeleportEffectComp->Activate();
	GetWorldTimerManager().SetTimer(TimerHandle_Teleport, FTimerDelegate::CreateLambda([&] { TeleportPlayer(); }), 0.2f, false);
}

void ASDashProjectile::TriggerTeleportOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (TeleportTriggered)
	{
		return;
	}
	TeleportTriggered = true;
	TeleportEffectComp->Activate();
	GetWorldTimerManager().SetTimer(TimerHandle_Teleport, FTimerDelegate::CreateLambda([&] { TeleportPlayer(); }), 0.2f, false);
}

void ASDashProjectile::TeleportPlayer()
{
	APawn* player = GetInstigator();
	if (player == nullptr)
	{
		return;
	}
	player->TeleportTo(GetActorLocation(), player->GetActorRotation(), false, true);
	Destroy();
}

void ASDashProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	EffectComp->OnSystemFinished.AddDynamic(this, &ASDashProjectile::TriggerTeleportTime);
	SphereComp->OnComponentHit.AddDynamic(this, &ASDashProjectile::TriggerTeleportOverlap);
}
