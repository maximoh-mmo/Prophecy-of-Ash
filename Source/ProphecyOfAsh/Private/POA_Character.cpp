//
// Copyright 2025 Max Heinze. All Rights Reserved.
//
// This file is part of the Prophecy of Ash project.
#include "POA_Character.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/GameplayCameraComponent.h"
#include "InputActionValue.h"
#include "InputDataConfig.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

// Sets default values
APOA_Character::APOA_Character()
{
	// Set up character defaults:
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -90.f), FQuat(FRotator(0.0f,-90.0f,0.0f)));
	RootComponent = GetMesh();
	CameraComp = CreateDefaultSubobject<UGameplayCameraComponent>(TEXT("GameplayCamera"));
	CameraComp->SetRelativeLocationAndRotation(FVector(0.f, 0.f, 100.f),FQuat(FRotator(0.f, 90.0f, 0.f)));
	CameraComp->SetupAttachment(GetMesh());

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

void APOA_Character::Move(const FInputActionValue& Value)
{
	auto move = Value.Get<FVector2D>();
	auto fwd = GetActorForwardVector();
	auto right = GetActorRightVector();
	auto rotation = GetControlRotation();
	AddMovementInput(right, move.X);
	AddMovementInput(fwd, move.Y);
}

void APOA_Character::LookGamepad(const FInputActionValue& Value)
{
	auto look = Value.Get<FVector2D>();
	auto dt = UGameplayStatics::GetWorldDeltaSeconds(this);
	AddControllerPitchInput(look.Y * dt);
	AddControllerYawInput(look.X);

}

void APOA_Character::Look(const FInputActionValue& Value)
{
	auto look = Value.Get<FVector2D>();
	AddControllerPitchInput(look.Y);
	AddControllerYawInput(look.X);
}

void APOA_Character::Interact(const FInputActionValue& Value)
{
	auto interact = Value.Get<bool>();
	if (interact)
	{
		UE_LOG(LogTemplateCharacter, Log, TEXT("Interacting!"));
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Log, TEXT("Not Interacting!"));
	}
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

		EnhancedInputComponent->BindAction(InputActions->MoveAction, ETriggerEvent::Triggered, this, &APOA_Character::Move);

		EnhancedInputComponent->BindAction(InputActions->LookAction, ETriggerEvent::Triggered, this, &APOA_Character::Look);

		EnhancedInputComponent->BindAction(InputActions->LookGamepadAction, ETriggerEvent::Triggered, this, &APOA_Character::LookGamepad);

	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void APOA_Character::AddHealth(float Amount)
{
	float NewHealth = FMath::Clamp(CurrentHealth + Amount, 0.f, MaxHealth);
	OnUpdateHealth.Broadcast(NewHealth, CurrentHealth, MaxHealth);
	CurrentHealth = NewHealth;
}

void APOA_Character::RemoveHealth(float Amount)
{
	float NewHealth = FMath::Clamp(CurrentHealth - Amount, 0.f, MaxHealth);
	OnUpdateHealth.Broadcast(NewHealth, CurrentHealth, MaxHealth);
	CurrentHealth = NewHealth;
}
