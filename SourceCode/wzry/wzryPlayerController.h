// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "wzryCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "AbilityTypes.h"
#include "wzryPlayerController.generated.h"

UCLASS()
class AwzryPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "wzryPlayerController")
		void AddAbilityToUI(FGameplayAbilityInfo AbilityInfo);


/*public:
	AwzryPlayerController();

protected:
	// True if the controlled character should navigate to the mouse cursor.
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	// Resets HMD orientation in VR. 
	void OnResetVR();

	// Navigate player to the current mouse cursor location. 
	void MoveToMouseCursor();

	// Navigate player to the current touch location. 
	void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);
	
	// Navigate player to the given world location. 
	void SetNewMoveDestination(const FVector DestLocation);

	// Input handlers for SetDestination action. 
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

	AwzryCharacter* MyCharacter = Cast<AwzryCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	*/
};


