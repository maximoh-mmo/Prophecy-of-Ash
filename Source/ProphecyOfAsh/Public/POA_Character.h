//
// Copyright 2025 Max Heinze. All Rights Reserved.
//
// This file is part of the Prophecy of Ash project.
#pragma once

#include "CoreMinimal.h"
#include "POA_Stats.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "AbilitySystemInterface.h"
#include "POA_Character.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FUpdateHealth, float, CurrentHP, float, LastHP, float, MaxHP);

UCLASS(config = Game)
class PROPHECYOFASH_API APOA_Character : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	APOA_Character();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FUpdateHealth OnUpdateHealth;

protected:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void BeginPlay() override;
	void Move(const FInputActionValue& Value);
	void GamepadLook(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	UFUNCTION(BlueprintNativeEvent)
	void BasicAttack(const FInputActionValue& Value);

	UFUNCTION(BlueprintNativeEvent)
	void SpecialAttack0(const FInputActionValue& Value);

	UFUNCTION(BlueprintNativeEvent)
	void SpecialAttack1(const FInputActionValue& Value);

	UFUNCTION(BlueprintNativeEvent)
	void SpecialAttack2(const FInputActionValue& Value);

	UFUNCTION(BlueprintNativeEvent)
	void ToggleLockOn(const FInputActionValue& Value);

	UFUNCTION(BlueprintNativeEvent)
	void NextLockOn(const FInputActionValue& Value);

	UFUNCTION(BlueprintNativeEvent)
	void PreviousLockOn(const FInputActionValue& Value);

	UFUNCTION(BlueprintNativeEvent)
	void Dodge(const FInputActionValue& Value);

	UFUNCTION(BlueprintNativeEvent)
	void Interact(const FInputActionValue& Value);

	UFUNCTION(BlueprintNativeEvent)
	void PauseGame(const FInputActionValue& Value);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	class UInputDataConfig* InputActions;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh")
	USkeletalMeshComponent* RetargetedMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
	const class UPOA_BasicAttributeSet* AttributeSet;
};