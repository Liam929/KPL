// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "LOL_TEST1GameMode.h"
#include "LOL_TEST1PlayerController.h"
#include "LOL_TEST1Character.h"
#include "UObject/ConstructorHelpers.h"

ALOL_TEST1GameMode::ALOL_TEST1GameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ALOL_TEST1PlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}