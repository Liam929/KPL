// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "WZRY0GameMode.h"
#include "WZRY0PlayerController.h"
#include "WZRY0Character.h"
#include "UObject/ConstructorHelpers.h"

AWZRY0GameMode::AWZRY0GameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AWZRY0PlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}