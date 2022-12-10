// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/BaseFlashLight.h"
#include "Engine/DirectionalLight.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/Character.h"
#include "Enemy/BaseEnemy.h"

ABaseFlashLight::ABaseFlashLight()
{
	PrimaryActorTick.bCanEverTick = true;

	FlashLightMesh = CreateDefaultSubobject<UStaticMeshComponent>("FlashLightMesh");
	FlashLightMesh->SetupAttachment(GetRootComponent());
	FlashLightMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	LightCollision = CreateDefaultSubobject<UStaticMeshComponent>("LightCollision");
	LightCollision->SetupAttachment(FlashLightMesh);
	LightCollision->SetVisibility(false, false);
	LightCollision->bHiddenInGame = true;
	LightCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	DirectionalLight = CreateDefaultSubobject<USpotLightComponent>("DirectionalLight");
	DirectionalLight->SetupAttachment(FlashLightMesh);
}

void ABaseFlashLight::BeginPlay()
{
	Super::BeginPlay();
	
	LightCollision->OnComponentBeginOverlap.AddDynamic(this, &ABaseFlashLight::OnCollisionOverlap);
}

void ABaseFlashLight::FlashLightUse()
{
	if (!Activated)
	{
		ToggleOnFlashLight();
	}
	else
	{
		ToggleOffFlashLight();
	}
}

void ABaseFlashLight::ToggleOnFlashLight()
{
	GetRootComponent()->SetVisibility(true, true);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("FlashLight On"));
	Activated = true;
	TArray<AActor*> Result;
	LightCollision->GetOverlappingActors(Result, ACharacter::StaticClass());

	for (auto ReceivedActor : Result)
	{
		if (ReceivedActor->IsA(ABaseEnemy::StaticClass()))
		{
			ReceivedActor->Destroy();
		}
	}
}

void ABaseFlashLight::ToggleOffFlashLight()
{
	GetRootComponent()->SetVisibility(false, true);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("FlashLight Off"));
	Activated = false;
}

void ABaseFlashLight::OnCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	if (OtherActor == GetOwner() || !Activated) return;

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Actor Was Destroyed"));
	OtherActor->Destroy();
}