// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UCameraComponent;
class ABaseFlashLight;

UCLASS()
class NIGHTSHADOW_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
		ABaseFlashLight* MainFlashLight = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Component")
	    TSubclassOf<ABaseFlashLight> FlashLightType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Component")
		UCameraComponent* MainCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Component")
		USceneComponent* LightPoint;

	void UseFlashLight();

private:
	void MoveForward(float Amount);
	void MoveRight(float Amount);
    
	void AttachFlashLight(ABaseFlashLight* FlashLight);
};
