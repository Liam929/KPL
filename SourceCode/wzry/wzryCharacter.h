// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include "wzryCharacter.generated.h"

class UAttributeSetBase;
class UGameplayAbilityBase;

UCLASS(Blueprintable)
class WZRY_API AwzryCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AwzryCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }
	

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UDecalComponent* CursorToWorld;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CharacterBase")
		UAbilitySystemComponent* AbilitySystemComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CharacterBase")
		UAttributeSetBase* AttributeSetBaseComp;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const ;

	// acquire ability
	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
		void AcquireAbility(TSubclassOf<UGameplayAbility> AbilityToAcquire);
	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
		void AcquireAbilities(TArray<TSubclassOf<UGameplayAbility> > AbilityToAcquire);

	// attribute functions
	UFUNCTION()
		void OnHealthChanged(float Health, float MaxHealth);
	UFUNCTION(BlueprintImplementableEvent, Category = "CharacterBase", meta = (DisplayName = "OnHealthChanged"))
		void BP_OnHealthChanged(float Health, float MaxHealth);
	UFUNCTION(BlueprintImplementableEvent, Category = "CharacterBase", meta = (DisplayName = "Die"))
		void BP_Die();

	UFUNCTION()
		void OnManaChanged(float Mana, float MaxMana);
	UFUNCTION(BlueprintImplementableEvent, Category = "CharacterBase", meta = (DisplayName = "OnManaChanged"))
		void BP_OnManaChanged(float Mana, float MaxMana);

	UFUNCTION()
		void OnEXPChanged(float EXP, float MaxEXP);
	UFUNCTION(BlueprintImplementableEvent, Category = "CharacterBase", meta = (DisplayName = "OnEXPChanged"))
		void BP_OnEXPChanged(float EXP, float MaxEXP);

	// compare team ID
	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
		bool IsOtherHostile(AwzryCharacter* Other);
	uint8 GetTeamID() const;


	// add fullhealth tag
	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
		void AddGameplayTag(FGameplayTag &TagToAdd);
	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
		void RemoveGameplayTag(FGameplayTag &TagToRemove);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterBase")
		FGameplayTag FullHealthTag;

	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
		void HitStun(float StunDuration);

	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
		void Respawn();

protected:

	bool bIsDead;
	uint8 TeamID;

	// if the character is player , TeamID = 0
	void AutoDeterminTeamIDbyControllerType();

	void Dead();

	// when attack or using skill , stop input
	void DisableInputControl();
	void EnableInputControl();
	FTimerHandle StunTimeHandle;

	void AddAbilityToUI(TSubclassOf<UGameplayAbilityBase> AbilityToAdd);
};

