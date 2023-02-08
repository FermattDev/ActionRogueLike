// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SInteractionComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<USInteractionComponent>("InteractionComp");

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;
}

void ASCharacter::PrimaryAttack_TimeElapsed(TSubclassOf<ASProjectile> ProjectileSpawn, FName SocketLocation)
{
	FVector HandLocation = GetMesh()->GetSocketLocation(SocketLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	UWorld* MyWorld = GetWorld();
	FHitResult Hit;

	FVector Start = CameraComp->GetComponentLocation();
	FRotator Rotation = CameraComp->GetComponentRotation();

	FVector End = (Start + (Rotation.Vector()) * 5000);

	MyWorld->LineTraceSingleByProfile(Hit, Start, End, "Projectile");

	FVector HitPosition = Hit.TraceEnd;

	if (Hit.IsValidBlockingHit())
	{
		HitPosition = Hit.ImpactPoint;

		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 5.0f, 32, FColor::Blue, false, 2.0f);
	}

	FTransform SpawnTM = FTransform((HitPosition - HandLocation).Rotation(), HandLocation);

	DrawDebugLine(GetWorld(), Start, End, FColor::Blue, false, 2.0f, 00, 2.0f);

	ASProjectile* Projectile = MyWorld->SpawnActor<ASProjectile>(ProjectileSpawn, SpawnTM, SpawnParams);
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ASCharacter::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	AddMovementInput(ControlRot.Vector(), Value);
}

void ASCharacter::MoveRight(float Value)
{
	FRotator controlRot = GetControlRotation();
	controlRot.Pitch = 0.0f;
	controlRot.Roll = 0.0f;

	FVector rightVector = FRotationMatrix(controlRot).GetScaledAxis(EAxis::Y);

	AddMovementInput(rightVector, Value);
}

void ASCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, FTimerDelegate::CreateLambda([&] { PrimaryAttack_TimeElapsed(ProjectileClass, "Muzzle_01"); }), 0.2f, false);
}

void ASCharacter::SecondaryAttack()
{
	PlayAnimMontage(SecondaryAttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, FTimerDelegate::CreateLambda([&] { PrimaryAttack_TimeElapsed(SecondaryClass, "Muzzle_01"); }), 0.2f, false);
}

void ASCharacter::UltimateAttack()
{
	PlayAnimMontage(UltimateAttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, FTimerDelegate::CreateLambda([&] { PrimaryAttack_TimeElapsed(UltimateClass, "Muzzle_01"); }), 0.2f, false);
}

void ASCharacter::PrimaryInteract()
{
	FVector location = CameraComp->GetComponentLocation();
	FRotator rotation = CameraComp->GetComponentRotation();

	UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"), *location.ToString(), *rotation.ToString());

	InteractionComp->PrimaryInteract(location, rotation);
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("SecondaryAttack", IE_Pressed, this, &ASCharacter::SecondaryAttack);
	PlayerInputComponent->BindAction("UltimateAttack", IE_Pressed, this, &ASCharacter::UltimateAttack);


	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ASCharacter::PrimaryInteract);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASCharacter::Jump);
}

