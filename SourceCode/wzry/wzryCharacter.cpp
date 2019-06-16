// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "wzryCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Engine.h"
#include "AbilitySystemComponent.h"
#include "AttributeSetBase.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "wzryPlayerController.h"
#include "GameplayAbilityBase.h"

AwzryCharacter::AwzryCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 950.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	// ability system component
	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystem");

	AttributeSetBaseComp = CreateDefaultSubobject<UAttributeSetBase>("AttributeSetBaseComp");

	// if the character is dead
	bIsDead = false;

	// set team ID
	TeamID = 255;

}

void AwzryCharacter::BeginPlay()
{

	Super::BeginPlay();

	// add attribute changed function to character
	AttributeSetBaseComp->OnHealthChange.AddDynamic(this, &AwzryCharacter::OnHealthChanged);
	AttributeSetBaseComp->OnManaChange.AddDynamic(this, &AwzryCharacter::OnManaChanged);
	AttributeSetBaseComp->OnEXPChange.AddDynamic(this, &AwzryCharacter::OnEXPChanged);

	// reset team ID to 0
	AutoDeterminTeamIDbyControllerType();

	// add full health tag
	AddGameplayTag(FullHealthTag);
}

UAbilitySystemComponent * AwzryCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComp;
}

void AwzryCharacter::AcquireAbility(TSubclassOf<UGameplayAbility> AbilityToAcquire)
{
	// give ability to character
	if (AbilitySystemComp) 
	{
		if (HasAuthority() && AbilityToAcquire) 
		{
			AbilitySystemComp->GiveAbility(FGameplayAbilitySpec(AbilityToAcquire, 1, 0));
		}
		AbilitySystemComp->InitAbilityActorInfo(this, this);
	}
}

void AwzryCharacter::AcquireAbilities(TArray<TSubclassOf<UGameplayAbility>> AbilityToAcquire)
{
	for (TSubclassOf<UGameplayAbility> AbilityItem : AbilityToAcquire)
	{
		AcquireAbility(AbilityItem);
		if (AbilityItem->IsChildOf(UGameplayAbilityBase::StaticClass()))
		{
			TSubclassOf<UGameplayAbilityBase> AbilityBaseClass = *AbilityItem;
			if (AbilityBaseClass != nullptr)
			{
				AddAbilityToUI(AbilityBaseClass);
			}
		}
	}
}

void AwzryCharacter::OnHealthChanged(float Health, float MaxHealth)
{
	// dead judge
	if (Health <= 0.f && !bIsDead)
	{
		bIsDead = true;
		Dead();
		BP_Die();
	}

	BP_OnHealthChanged(Health, MaxHealth);

}

void AwzryCharacter::OnManaChanged(float Mana, float MaxMana)
{

	BP_OnManaChanged(Mana, MaxMana);
}

void AwzryCharacter::OnEXPChanged(float EXP, float MaxEXP)
{
	BP_OnEXPChanged(EXP, MaxEXP);
}

bool AwzryCharacter::IsOtherHostile(AwzryCharacter * Other)
{
	return TeamID != Other->GetTeamID();
}

uint8 AwzryCharacter::GetTeamID() const
{
	return TeamID;
}

void AwzryCharacter::AddGameplayTag(FGameplayTag & TagToAdd)
{
	GetAbilitySystemComponent()->AddLooseGameplayTag(TagToAdd);
	GetAbilitySystemComponent()->SetTagMapCount(TagToAdd, 1);
}

void AwzryCharacter::RemoveGameplayTag(FGameplayTag & TagToRemove)
{
	GetAbilitySystemComponent()->RemoveLooseGameplayTag(TagToRemove);
}

void AwzryCharacter::HitStun(float StunDuration)
{
	DisableInputControl();
	GetWorldTimerManager().SetTimer(StunTimeHandle, this, &AwzryCharacter::EnableInputControl, StunDuration, false);

}

void AwzryCharacter::Respawn()
{
	bIsDead = false;
	EnableInputControl();
}
 
void AwzryCharacter::AutoDeterminTeamIDbyControllerType()
{
	// is controlled player , set TeamID = 0
	if (GetController() && GetController()->IsPlayerController())
	{
		TeamID = 0;
	}
}

void AwzryCharacter::Dead()
{
	DisableInputControl();
}

void AwzryCharacter::DisableInputControl()
{
	// stop palyer input when died
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		PC->DisableInput(PC);
	}

	// stop AI logic when died
	AAIController* AIC = Cast<AAIController>(GetController());
	if (AIC)
	{
		AIC->GetBrainComponent()->StopLogic("Dead");
	}

}

void AwzryCharacter::EnableInputControl()
{
	if (!bIsDead)
	{
		// enable palyer input 
		APlayerController* PC = Cast<APlayerController>(GetController());
		if (PC)
		{
			PC->EnableInput(PC);
		}

		// enable AI logic 
		AAIController* AIC = Cast<AAIController>(GetController());
		if (AIC)
		{
			AIC->GetBrainComponent()->RestartLogic();
		}
	}
}

void AwzryCharacter::AddAbilityToUI(TSubclassOf<UGameplayAbilityBase> AbilityToAdd)
{
	AwzryPlayerController* PlayerControllerBase = Cast<AwzryPlayerController>(GetController());
	if (PlayerControllerBase)
	{
		UGameplayAbilityBase* AbilityInstance = AbilityToAdd.Get()->GetDefaultObject<UGameplayAbilityBase>();
		if (AbilityInstance)
		{
			FGameplayAbilityInfo AbilityInfo = AbilityInstance->GetAbilityInfo();
			PlayerControllerBase->AddAbilityToUI(AbilityInfo);
		}
	}
}

void AwzryCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	if (CursorToWorld != nullptr)
	{
		if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		{
			if (UWorld* World = GetWorld())
			{
				FHitResult HitResult;
				FCollisionQueryParams Params(NAME_None, FCollisionQueryParams::GetUnknownStatId());
				FVector StartLocation = TopDownCameraComponent->GetComponentLocation();
				FVector EndLocation = TopDownCameraComponent->GetComponentRotation().Vector() * 2000.0f;
				Params.AddIgnoredActor(this);
				World->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params);
				FQuat SurfaceRotation = HitResult.ImpactNormal.ToOrientationRotator().Quaternion();
				CursorToWorld->SetWorldLocationAndRotation(HitResult.Location, SurfaceRotation);
			}
		}
		else if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}
}


