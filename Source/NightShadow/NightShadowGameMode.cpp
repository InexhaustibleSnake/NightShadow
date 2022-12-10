// Copyright Epic Games, Inc. All Rights Reserved.

#include "NightShadowGameMode.h"
#include "NightShadowCharacter.h"
#include "UObject/ConstructorHelpers.h"

ANightShadowGameMode::ANightShadowGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
