// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
//�Ķ�1�����ͷ�ļ�
#include "LOL_TEST1Character.generated.h"

UCLASS(Blueprintable)
class ALOL_TEST1Character : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ALOL_TEST1Character();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }
	UAbilitySystemComponent* GetAbilitySystemComponent()const override;
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
	//�Ķ�3�����һ��Abi���
	//BlueprintReadOnly��������ʵ�ǲ�����д��private���еģ����д��private����Ҫ��ͼ�ɶ�����ô��Ҫд��meta=(AllowPrivateAccess="true")
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GameplayAbilities, meta = (AllowPrivateAccess = "true"))
		class UAbilitySystemComponent* AbilitySystem;
};

