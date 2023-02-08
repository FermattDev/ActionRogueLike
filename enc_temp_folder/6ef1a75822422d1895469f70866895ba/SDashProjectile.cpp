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
	TeleportEffectComp->Activate();
	GetWorldTimerManager().SetTimer(TimerHandle_Teleport, FTimerDelegate::CreateLambda([&] { TeleportPlayer(); }), 0.2f, false);
}

void ASDashProjectile::TriggerTeleportOverlap(UPrimitiveComponent* OnComponentBeginOverlap, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TeleportEffectComp->Activate();
	GetWorldTimerManager().SetTimer(TimerHandle_Teleport, FTimerDelegate::CreateLambda([&] { TeleportPlayer(); }), 0.2f, false);
}

void ASDashProjectile::TriggerTeleport()
{
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
	player->SetActorRelativeLocation(GetActorLocation());
}

void ASDashProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	EffectComp->OnSystemFinished.AddDynamic(this, &ASDashProjectile::TriggerTeleportTime);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASDashProjectile::TriggerTeleportOverlap);
}
