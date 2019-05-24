// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Pawn.h"
#include "SphereBase.generated.h"

UCLASS()
class WZRY0_API ASphereBase : public APawn
{
	GENERATED_BODY()


public:
	// Sets default values for this pawn's properties
	ASphereBase();

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent *SphereBase;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
