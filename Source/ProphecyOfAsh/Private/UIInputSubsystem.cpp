// Fill out your copyright notice in the Description page of Project Settings.


#include "UIInputSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Kismet/GameplayStatics.h"

void UUIInputSubsystem::HandleWidgetPushed(UUserWidget* Widget)
{
	if (!Widget)
	{
		return;
	}

	// Search for Default Widget
	UWidget* FocusTarget = Widget->GetWidgetFromName(FName("DefaultFocus"));

	// Fallback: Take First visible and focusable Widget available
	if (!FocusTarget)
	{
		TArray<UWidget*> AllWidgets;
		Widget->WidgetTree->GetAllWidgets(AllWidgets);
		for (UWidget* W : AllWidgets)
		{
			if (W && W->GetVisibility() == ESlateVisibility::Visible)
			{
				FocusTarget = W;
				break;
			}
		}
	}

	if (FocusTarget)
	{
		SetFocusToWidget(FocusTarget);
	}
}

void UUIInputSubsystem::SetFocusToWidget(UWidget* Widget)
{
	if (!Widget || !Widget->IsVisible())
	{
		return;
	}

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PC)
	{
		return;
	}

	PC->SetInputMode(FInputModeUIOnly()
		.SetWidgetToFocus(Widget->TakeWidget())
		.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock));
	PC->SetShowMouseCursor(true);
	//PC->SetUserFocus(Widget);

	ApplySlateFocus(Widget);
}

void UUIInputSubsystem::ApplySlateFocus(UWidget* Widget)
{
	/*if (TSharedPtr<SWidget> SlateWidget = Widget->GetCachedWidget())
	{
		FSlateApplication::Get().SetKeyboardFocus(SlateWidget, EFocusCause::SetDirectly);
	}*/
}
