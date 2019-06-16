// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeSetBase.h"
#include "GameplayEffectExtension.h"
#include "Public/GameplayEffect.h"
#include "wzryCharacter.h"

UAttributeSetBase::UAttributeSetBase()
	:Health(1000.f)
	,MaxHealth(1000.f)
	,Mana(400.f)
	,MaxMana(400.f)
	,Level(1.f)
	,EXP(0.f)
	,MaxEXP(200.f)
	,Gold(0.f)
	,K(0.f)
	,D(0.f)
	,AttackDamage(80.f)
	,Armor(0.f)
	,WeaponSlotsNum(0.f)
{

}

bool UAttributeSetBase::LevelUP()
{
	if (EXP.GetCurrentValue() >= MaxEXP.GetCurrentValue())
	{
		Level.SetCurrentValue(Level.GetCurrentValue() + 1);
		ClearEXP();
		return true;
	}
	else return false;
}

void UAttributeSetBase::IncreaseEXP(float EXPToIncrease)
{
	EXP.SetCurrentValue(EXP.GetCurrentValue() + EXPToIncrease);
}


void UAttributeSetBase::ClearEXP()
{
	EXP.SetCurrentValue(EXP.GetCurrentValue() - MaxEXP.GetCurrentValue());
}

void UAttributeSetBase::IncreaseGold(float GoldToIncrease)
{
	Gold.SetCurrentValue(Gold.GetCurrentValue() + GoldToIncrease);
}

bool UAttributeSetBase::CostGold(float GoldToCost)
{
	if (Gold.GetCurrentValue() < GoldToCost && Gold.GetCurrentValue() >= 0)
	{
		Gold.SetCurrentValue(Gold.GetCurrentValue() - GoldToCost);
		return true;
	}
	else return false;
}

void UAttributeSetBase::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data)
{
	// change health
	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<UProperty>(UAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSetBase, Health)))
	{
		// set min health
		Health.SetCurrentValue(FMath::Clamp(Health.GetCurrentValue(), 0.f, MaxHealth.GetCurrentValue()));
		Health.SetBaseValue(FMath::Clamp(Health.GetBaseValue(), 0.f, MaxHealth.GetCurrentValue()));
		OnHealthChange.Broadcast(Health.GetCurrentValue(), MaxHealth.GetCurrentValue());

		// judge if or not add full health tag
		AwzryCharacter* CharacterOwner = Cast<AwzryCharacter>(GetOwningActor());
		if (Health.GetCurrentValue() == MaxHealth.GetCurrentValue())
		{
			if (CharacterOwner)
			{
				CharacterOwner->AddGameplayTag(CharacterOwner->FullHealthTag);
			}
		}
		else
		{
			if (CharacterOwner)
			{
				CharacterOwner->RemoveGameplayTag(CharacterOwner->FullHealthTag);
			}
		}
	}

	// change mana
	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<UProperty>(UAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSetBase, Mana)))
	{
		// set min mana
		Mana.SetCurrentValue(FMath::Clamp(Mana.GetCurrentValue(), 0.f, MaxMana.GetCurrentValue()));
		Mana.SetBaseValue(FMath::Clamp(Mana.GetBaseValue(), 0.f, MaxMana.GetCurrentValue()));
		OnManaChange.Broadcast(Mana.GetCurrentValue(), MaxMana.GetCurrentValue());
	}

	// change EXP
	/*if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<UProperty>(UAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSetBase, EXP)))
	{
		// set min and max EXP
		EXP.SetCurrentValue(FMath::Clamp(EXP.GetCurrentValue(), 0.f, MaxEXP.GetCurrentValue()));
		EXP.SetBaseValue(FMath::Clamp(EXP.GetBaseValue(), 0.f, MaxEXP.GetCurrentValue()));
		OnEXPChange.Broadcast(EXP.GetCurrentValue(), MaxEXP.GetCurrentValue());
	}*/
}
