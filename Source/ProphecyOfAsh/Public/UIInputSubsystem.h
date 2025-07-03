// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UIInputSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class PROPHECYOFASH_API UUIInputSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	/** Gets called when a new Widget gets pushed on the Stack */
	UFUNCTION(BlueprintCallable)
	void HandleWidgetPushed(UUserWidget* Widget);

	/** Sets Focus on a Widget and handles Slate & User Focus */
	UFUNCTION(BlueprintCallable)
	void SetFocusToWidget(UWidget* Widget);

protected:
	void ApplySlateFocus(UWidget* Widget);
	
};
