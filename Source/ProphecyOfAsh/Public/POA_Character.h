//
// Copyright 2025 Max Heinze. All Rights Reserved.
//
// This file is part of the Prophecy of Ash project.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "POA_Character.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FUpdateHealth, float, CurrentHP, float, LastHP, float, MaxHP);

UCLASS()
class PROPHECYOFASH_API APOA_Character : public ACharacter
{
	GENERATED_BODY()

public:
	APOA_Character();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Health")
	void AddHealth(float Amount);
	UFUNCTION(BlueprintCallable, Category = "Health")
	void RemoveHealth(float Amount);

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FUpdateHealth OnUpdateHealth;

protected:

	virtual void BeginPlay() override;
	void Move(const FInputActionValue& Value);
	void LookGamepad(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Interact(const FInputActionValue& Value);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UGameplayCameraComponent* CameraComp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput")
	class UInputDataConfig* InputActions;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput")
	class UInputMappingContext* InputMapping;

private:
	UPROPERTY()
	float MaxHealth = 100.f;
	UPROPERTY()
	float CurrentHealth = 100.f;
};
