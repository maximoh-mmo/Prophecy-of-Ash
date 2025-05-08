//
// Copyright 2025 Max Heinze. All Rights Reserved.
//
// This file is part of the Prophecy of Ash project.
#include "POA_Character.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputActionValue.h"
#include "InputDataConfig.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

// Sets default values
APOA_Character::APOA_Character()
{
	// Set up character defaults:
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -90.f), FQuat(FRotator(0.0f,-90.0f,0.0f)));

	SpringArmComp->SetupAttachment(GetMesh());
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);

	SpringArmComp->bUsePawnControlRotation = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bIgnoreBaseRotation = true;

	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APOA_Character::BeginPlay()
{
	Super::BeginPlay();
}

void APOA_Character::MoveForward(const FInputActionValue& Value)
{
	float FloatValue = Value.Get<float>();

	if ((Controller != nullptr) && (FloatValue != 0.0f))
	{
		// Find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, FloatValue);
	}
}

void APOA_Character::MoveRight(const FInputActionValue& Value)
{
	float FloatValue = Value.Get<float>();
	if ((Controller != nullptr) && (FloatValue != 0.0f))
	{
		// Find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		// Get right vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, FloatValue);
	}
}

void APOA_Character::MoveCameraIn(const FInputActionValue& Value)
{
	float FloatValue = Value.Get<float>();

	if (Controller != nullptr && FloatValue != 0.0f)
	{
		CameraComp->SetRelativeLocation(CameraComp->GetRelativeLocation() + FVector(FloatValue, 0.f, 0.f));
	}
}

void APOA_Character::Turn(const FInputActionValue& Value)
{
	UE_LOG(LogTemplateCharacter, Log, TEXT("Turn Value: %s"), *Value.ToString());
	AddControllerYawInput(Value.Get<float>());
}

// Called every frame
void APOA_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APOA_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{

		if (!InputActions) return;

		UE_LOG(LogTemplateCharacter, Log, TEXT("'%s' Found an Enhanced Input Component!"), *GetNameSafe(this));

		EnhancedInputComponent->BindAction(InputActions->TurnAction, ETriggerEvent::Triggered, this, &APOA_Character::Turn);

		EnhancedInputComponent->BindAction(InputActions->MoveForwardAction, ETriggerEvent::Triggered, this, &APOA_Character::MoveForward);

		EnhancedInputComponent->BindAction(InputActions->MoveRightAction, ETriggerEvent::Triggered, this, &APOA_Character::MoveRight);

		EnhancedInputComponent->BindAction(InputActions->MoveCameraInAction, ETriggerEvent::Triggered, this, &APOA_Character::MoveCameraIn);

	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}