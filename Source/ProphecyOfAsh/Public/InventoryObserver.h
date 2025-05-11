#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InventoryObserver.generated.h"


class UItem;
class UInventory;

UINTERFACE(MinimalAPI, Blueprintable)
class UInventoryObserver : public UInterface
{
	GENERATED_BODY()
};

class IInventoryObserver
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Inventory")
	void OnItemAdded(UInventory* Inventory, UItem* Item);

	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Inventory")
	void OnItemRemoved(UInventory* Inventory, UItem* Item);


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Inventory")
	void OnItemUsed(UInventory* Inventory, UItem* Item);


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Inventory")
	void OnItemEquipped(UInventory* Inventory, UItem* Item);


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Inventory")
	void OnItemUnequipped(UInventory* Inventory, UItem* Item);
};

