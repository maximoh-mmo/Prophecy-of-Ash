#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item.h"
#include "Inventory.generated.h"

//class UItem;
//class UInventory;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemAddedSignature, UInventory*, Inventory, UItem*, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemRemovedSignature, UInventory*, Inventory, UItem*, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemUsedSignature, UInventory*, Inventory, UItem*, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemEquippedSignature, UInventory*, Inventory, UItem*, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemUnequippedSignature, UInventory*, Inventory, UItem*, Item);

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
class PROPHECYOFASH_API UInventory : public UActorComponent
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

public:    
    UInventory();
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    int32 MaxSlots;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
    TArray<FInventorySlot> Slots;

    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
    TArray<UItem*> EquippedItems;


    UPROPERTY(BlueprintAssignable, Category = "Inventory|Events")
    FOnItemAddedSignature OnItemAdded;

    UPROPERTY(BlueprintAssignable, Category = "Inventory|Events")
    FOnItemRemovedSignature OnItemRemoved;

    UPROPERTY(BlueprintAssignable, Category = "Inventory|Events")
    FOnItemUsedSignature OnItemUsed;

    UPROPERTY(BlueprintAssignable, Category = "Inventory|Events")
    FOnItemEquippedSignature OnItemEquipped;

    UPROPERTY(BlueprintAssignable, Category = "Inventory|Events")
    FOnItemUnequippedSignature OnItemUnequipped;

    
    UFUNCTION(BlueprintCallable, Category = "Inventory|Events")
    void NotifyItemAdded(UItem* Item);

    UFUNCTION(BlueprintCallable, Category = "Inventory|Events")
    void NotifyItemRemoved(UItem* Item);

    UFUNCTION(BlueprintCallable, Category = "Inventory|Events")
    void NotifyItemUsed(UItem* Item);

    UFUNCTION(BlueprintCallable, Category = "Inventory|Events")
    void NotifyItemEquipped(UItem* Item);

    UFUNCTION(BlueprintCallable, Category = "Inventory|Events")
    void NotifyItemUnequipped(UItem* Item);

  
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool AddItem(UItem* Item, int32 Quantity = 1);


    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool RemoveItem(UItem* Item, int32 Quantity = 1);

    
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool UseItem(UItem* Item);

   
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool EquipItem(UItem* Item);

  
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool UnequipItem(UItem* Item);
    

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    int32 GetItemCount(UItem* ItemTemplate) const;

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    TArray<UItem*> GetItemsByType(EItemType Type) const;

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool HasItem(UItem* ItemTemplate, int32 Quantity = 1) const;

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool IsItemEquipped(UItem* Item) const;
};