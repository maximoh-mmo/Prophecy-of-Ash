#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "POA_Item.h"
#include "POA_Inventory.generated.h"

//class APOA_Item;
//class UPOA_Inventory;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemAddedSignature, UPOA_Inventory*, Inventory, APOA_Item*, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemRemovedSignature, UPOA_Inventory*, Inventory, APOA_Item*, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemUsedSignature, UPOA_Inventory*, Inventory, APOA_Item*, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemEquippedSignature, UPOA_Inventory*, Inventory, APOA_Item*, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemUnequippedSignature, UPOA_Inventory*, Inventory, APOA_Item*, Item);

USTRUCT(BlueprintType)
struct FInventorySlot
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    APOA_Item* Item;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    int32 Quantity;

    FInventorySlot()
        : Item(nullptr)
        , Quantity(0)
    {
    }

    FInventorySlot(APOA_Item* InItem, int32 InQuantity)
        : Item(InItem)
        , Quantity(InQuantity)
    {
    }
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROPHECYOFASH_API UPOA_Inventory : public UActorComponent
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

public:    
    UPOA_Inventory();
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    int32 MaxSlots;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
    TArray<FInventorySlot> Slots;

    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
    TArray<APOA_Item*> EquippedItems;


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
    void NotifyItemAdded(APOA_Item* Item);

    UFUNCTION(BlueprintCallable, Category = "Inventory|Events")
    void NotifyItemRemoved(APOA_Item* Item);

    UFUNCTION(BlueprintCallable, Category = "Inventory|Events")
    void NotifyItemUsed(APOA_Item* Item);

    UFUNCTION(BlueprintCallable, Category = "Inventory|Events")
    void NotifyItemEquipped(APOA_Item* Item);

    UFUNCTION(BlueprintCallable, Category = "Inventory|Events")
    void NotifyItemUnequipped(APOA_Item* Item);

  
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool AddItem(APOA_Item* Item, int32 Quantity = 1);


    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool RemoveItem(APOA_Item* Item, int32 Quantity = 1);

    
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool UseItem(APOA_Item* Item);

   
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool EquipItem(APOA_Item* Item);

  
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool UnequipItem(APOA_Item* Item);
    

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    int32 GetItemCount(APOA_Item* ItemTemplate) const;

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    TArray<APOA_Item*> GetItemsByType(EItemType Type) const;

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool HasItem(APOA_Item* ItemTemplate, int32 Quantity = 1) const;

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool IsItemEquipped(APOA_Item* Item) const;
};