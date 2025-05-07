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

UCLASS()
class PROPHECYOFASH_API APOA_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APOA_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UCameraComponent* CameraComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput")
	class UInputDataConfig* InputActions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput")
	class UInputMappingContext* InputMapping;
	
	void MoveForward(const FInputActionValue& Value);
	void MoveRight(const FInputActionValue& Value);
	void MoveCameraIn(const FInputActionValue& Value);
	void Turn(const FInputActionValue& Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

};
