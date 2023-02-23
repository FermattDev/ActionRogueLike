// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"
#include "SAttributeComponent.h"
#include "Components/AudioComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"

// Sets default values
ASMagicProjectile::ASMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FlightAudio = CreateDefaultSubobject<UAudioComponent>("AudioComp");
	FlightAudio->SetupAttachment(SphereComp);
	FlightAudio->bAutoActivate = true;

	Damage = 20.0f;
}

void ASMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (AttributeComp)
		{
			AttributeComp->ApplyHealthChange(GetInstigator(), -Damage);
		}

		UGameplayStatics::PlayWorldCameraShake(this, ImpactStrike, GetActorLocation(), 0, 10000);
		DestroyProjectile();
	}
}

void ASMagicProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* instigator = GetInstigator();
	if (OtherActor && OtherActor != instigator)
	{
		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (AttributeComp)
		{
			AttributeComp->ApplyHealthChange(GetInstigator(), -Damage);
		}

		UGameplayStatics::PlayWorldCameraShake(this, ImpactStrike, GetActorLocation(), 0, 1000);
		DestroyProjectile();
	}
}

void ASMagicProjectile::DestroyProjectile()
{
	if (IsValid(this))
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), DestroySound, GetActorLocation());
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyEffect, GetTransform());
		Destroy();
	}
}

// Called when the game starts or when spawned
void ASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);

	FlightAudio->Play();

	GetWorldTimerManager().SetTimer(TimerHandle_Destroy, FTimerDelegate::CreateLambda([&] {
			DestroyProjectile();
		}), 5.0f, false);
}

// Called every frame
void ASMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASMagicProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectile::OnActorOverlap);
	SphereComp->OnComponentHit.AddDynamic(this, &ASMagicProjectile::OnActorHit);
}