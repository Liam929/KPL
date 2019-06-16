// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "GATargetActorGroundSelect.generated.h"

class UDecalComponent;
class USceneComponent;
/**
 * 
 */
UCLASS()
class WZRY_API AGATargetActorGroundSelect : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()
	
public:

	AGATargetActorGroundSelect();

	virtual void Tick(float DeltaSeconds) override;

	virtual void StartTargeting(UGameplayAbility* Ability);
	virtual void ConfirmTargetingAndContinue() override;

	UFUNCTION(BlueprintCallable, Category = "GroundSelect")
		bool  GetPlayerLookingPoint(FVector& OutViewPoint);

	// skill circle range
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "GroundSelect")
		float Radius;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GroundBlast")
		UDecalComponent* Decal;

	USceneComponent* RootComp;
};
