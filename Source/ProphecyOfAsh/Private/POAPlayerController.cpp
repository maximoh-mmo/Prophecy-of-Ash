#include "POAPlayerController.h"
#include "Blueprint/UserWidget.h"

APOAPlayerController::APOAPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}

void APOAPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void APOAPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}


// Focuses the Input on the UI
void APOAPlayerController::FocusUI(UUserWidget* FocusTarget, bool bShowCursor, bool bPauseGame)
{
	SetShowMouseCursor(bShowCursor);

	FInputModeUIOnly InputMode;
	if (FocusTarget)
	{
		InputMode.SetWidgetToFocus(FocusTarget->TakeWidget());
	}
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputMode);

	if (bPauseGame)
	{
		SetPause(true);
	}
}

// Focuses the Input on the Game
void APOAPlayerController::FocusGame()
{
	SetShowMouseCursor(false);
	SetInputMode(FInputModeGameOnly());
	SetPause(false);
}

