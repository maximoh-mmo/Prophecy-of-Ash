#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "POAPlayerController.generated.h"

class UUserWidget;

/**
 * PlayerController that also manages the stack-based UI layer system.
 */

UCLASS()
class PROPHECYOFASH_API APOAPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	APOAPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

public:
	/** Focuses UI mode (UI-only input, show cursor) */
	UFUNCTION(BlueprintCallable, Category = "UI")
	void FocusUI(UUserWidget* FocusTarget = nullptr, bool bShowCursor = true, bool bPauseGame = false);

	/** Returns input to game mode (hide cursor, unpause) */
	UFUNCTION(BlueprintCallable, Category = "UI")
	void FocusGame();
	
};
