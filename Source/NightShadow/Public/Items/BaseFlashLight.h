// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseFlashLight.generated.h"

class UStaticMeshComponent;
class USpotLightComponent;

UCLASS()
class NIGHTSHADOW_API ABaseFlashLight : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseFlashLight();
	void FlashLightUse();
	void ToggleOnFlashLight();
	void ToggleOffFlashLight();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Component")
		UStaticMeshComponent* FlashLightMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Component")
		UStaticMeshComponent* LightCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Component")
		USpotLightComponent* DirectionalLight;
	
	UFUNCTION()
		void OnCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);

	bool Activated = false;
};