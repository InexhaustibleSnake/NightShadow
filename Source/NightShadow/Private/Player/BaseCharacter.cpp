// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/BaseCharacter.h"
#include "Components/SceneComponent.h"
#include "Camera/CameraComponent.h"
#include "Items/BaseFlashLight.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	MainCamera = CreateDefaultSubobject<UCameraComponent>("MainCamera");
	MainCamera->SetupAttachment(GetMesh(), "head");

	LightPoint = CreateDefaultSubobject<USceneComponent>("FlashLightSpawn");
	LightPoint->SetupAttachment(GetRootComponent());
}
 
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	MainFlashLight = GetWorld()->SpawnActor<ABaseFlashLight>(FlashLightType);
	MainFlashLight->SetOwner(this);
	AttachFlashLight(MainFlashLight);
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("FlashLight", IE_Pressed, this, &ABaseCharacter::UseFlashLight);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("MouseX", this, &ABaseCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("MouseY", this, &ABaseCharacter::AddControllerPitchInput);
}

void ABaseCharacter::MoveForward(float Amount)
{
	AddMovementInput(GetActorForwardVector(), Amount);
}

void ABaseCharacter::MoveRight(float Amount)
{
	AddMovementInput(GetActorRightVector(), Amount);
}

void ABaseCharacter::UseFlashLight()
{
	MainFlashLight->FlashLightUse();
}

void ABaseCharacter::AttachFlashLight(ABaseFlashLight* FlashLight)
{
	if (!FlashLight || !LightPoint) return;
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepRelative, false);
	FlashLight->AttachToComponent(LightPoint, AttachmentRules);
}