// Copyright Epic Games, Inc. All Rights Reserved.

#include "LiquidXGameMode.h"
#include "LiquidXCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALiquidXGameMode::ALiquidXGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
