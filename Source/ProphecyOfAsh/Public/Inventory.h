#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item.h"
#include "InventoryObserver.h"
#include "Inventory.generated.h"

USTRUCT(BlueprintType)
struct FInventorySlot
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    UItem* Item;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    int32 Quantity;

    FInventorySlot()
        : Item(nullptr)
        , Quantity(0)
    {
    }

    FInventorySlot(UItem* InItem, int32 InQuantity)
        : Item(InItem)
        , Quantity(InQuantity)
    {
    }
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class YOUR_API UInventory : public UActorComponent
{
    GENERATED_BODY()

public:    
    UInventory();

protected:
    virtual void BeginPlay() override;

public:    
    // Maximum number of items this inventory can hold
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    int32 MaxSlots;

    // Maximum weight this inventory can hold
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    float MaxWeight;

    // Current items in the inventory
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
    TArray<FInventorySlot> Slots;

    // Currently equipped items
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
    TArray<UItem*> EquippedItems;

    // Observer pattern implementation
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
    TArray<TScriptInterface<IInventoryObserver>> Observers;

    // Add an observer
    UFUNCTION(BlueprintCallable, Category = "Inventory|Observer")
    void AddObserver(TScriptInterface<IInventoryObserver> Observer);

    // Remove an observer
    UFUNCTION(BlueprintCallable, Category = "Inventory|Observer")
    void RemoveObserver(TScriptInterface<IInventoryObserver> Observer);

    // Notify all observers about an item being added
    UFUNCTION(BlueprintCallable, Category = "Inventory|Observer")
    void NotifyItemAdded(UItem* Item);

    // Notify all observers about an item being removed
    UFUNCTION(BlueprintCallable, Category = "Inventory|Observer")
    void NotifyItemRemoved(UItem* Item);

    // Notify all observers about an item being used
    UFUNCTION(BlueprintCallable, Category = "Inventory|Observer")
    void NotifyItemUsed(UItem* Item);

    // Notify all observers about an item being equipped
    UFUNCTION(BlueprintCallable, Category = "Inventory|Observer")
    void NotifyItemEquipped(UItem* Item);

    // Notify all observers about an item being unequipped
    UFUNCTION(BlueprintCallable, Category = "Inventory|Observer")
    void NotifyItemUnequipped(UItem* Item);

    // Add item to inventory
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool AddItem(UItem* Item, int32 Quantity = 1);

    // Remove item from inventory
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool RemoveItem(UItem* Item, int32 Quantity = 1);

    // Use an item from inventory
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool UseItem(UItem* Item);

    // Equip an item from inventory
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool EquipItem(UItem* Item);

    // Unequip an item
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool UnequipItem(UItem* Item);

    // Helper functions
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    float GetCurrentWeight() const;

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    int32 GetItemCount(UItem* ItemTemplate) const;

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    TArray<UItem*> GetItemsByType(EItemType Type) const;

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool HasItem(UItem* ItemTemplate, int32 Quantity = 1) const;

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool IsItemEquipped(UItem* Item) const;
};