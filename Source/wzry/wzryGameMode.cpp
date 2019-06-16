// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "wzryGameMode.h"
#include "wzryPlayerController.h"
#include "wzryCharacter.h"
#include "UObject/ConstructorHelpers.h"

AwzryGameMode::AwzryGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AwzryPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprint/Character/BP_CharacterBase"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

}