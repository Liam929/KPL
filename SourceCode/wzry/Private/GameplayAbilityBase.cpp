// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilityBase.h"

FGameplayAbilityInfo  UGameplayAbilityBase::GetAbilityInfo()
{
	UGameplayEffect* CDEffect = GetCooldownGameplayEffect();
	UGameplayEffect* CostEffect = GetCostGameplayEffect();
	if (CDEffect && CostEffect)
	{
		float CDDuration = 0;
		CDEffect->DurationMagnitude.GetStaticMagnitudeIfPossible(1, CDDuration);
		float Cost = 0;
		EAbilityCostType CostType;
		if (CostEffect->Modifiers.Num() > 0)
		{
			FGameplayModifierInfo EffectInfo = CostEffect->Modifiers[0];
			EffectInfo.ModifierMagnitude.GetStaticMagnitudeIfPossible(1, Cost);
			FGameplayAttribute CostAttribute = EffectInfo.Attribute;
			FString AttributeName = CostAttribute.AttributeName;
			if (AttributeName == "Health")
			{
				CostType = EAbilityCostType::Health;
			}
			else if (AttributeName == "Mana")
			{
				CostType = EAbilityCostType::Mana;
			}
			return FGameplayAbilityInfo(CDDuration, Cost, CostType, UIMaterial, GetClass());
		}
	}

	return FGameplayAbilityInfo();
}
