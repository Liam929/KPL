// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AttributeSetBase.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChangeDelegate, float, Health, float, MaxHealth);

UCLASS()
class WZRY_API UAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()

public:

	UAttributeSetBase();

	// set attributes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSetBase")
		FGameplayAttributeData Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSetBase")
		FGameplayAttributeData MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSetBase")
		FGameplayAttributeData Mana;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSetBase")
		FGameplayAttributeData MaxMana;

	// ----------------------------------- //
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSetBase")
		FGameplayAttributeData Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSetBase")
		FGameplayAttributeData EXP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSetBase")
		FGameplayAttributeData MaxEXP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSetBase")
		FGameplayAttributeData Gold;

	UFUNCTION(BlueprintCallable, Category = "AttributeSetBase")
		bool LevelUP();
	UFUNCTION(BlueprintCallable, Category = "AttributeSetBase")
		void IncreaseEXP(float EXPToIncrease);
	UFUNCTION(BlueprintCallable, Category = "AttributeSetBase")
		void ClearEXP();
	UFUNCTION(BlueprintCallable, Category = "AttributeSetBase")
		void IncreaseGold(float GoldToIncrease);
	UFUNCTION(BlueprintCallable, Category = "AttributeSetBase")
		bool CostGold(float GoldToCost);

	// kill number
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSetBase")
		FGameplayAttributeData K;
	// death number
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSetBase")
		FGameplayAttributeData D;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSetBase")
		FGameplayAttributeData AttackDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSetBase")
		FGameplayAttributeData Armor;

	// weapon	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSetBase")
		FGameplayAttributeData WeaponSlotsNum;

	
	// ------------------------------------ //

	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data) override;
	
	FOnHealthChangeDelegate OnHealthChange;
	FOnHealthChangeDelegate OnManaChange;
	FOnHealthChangeDelegate OnEXPChange;

};
