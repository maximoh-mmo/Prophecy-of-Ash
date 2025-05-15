#pragma once

#include "CoreMinimal.h"
#include "Item.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
    Potion  UMETA(DisplayName = "Potion"),
    Weapon  UMETA(DisplayName = "Weapon"),
    Misc    UMETA(DisplayName = "Miscellaneous")
};

UCLASS(Abstract, BlueprintType, Blueprintable)
class PROPHECYOFASH_API UItem : public UObject
{
    GENERATED_BODY()

public:
    UItem();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FString Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    UTexture2D* Icon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    int32 MaxStackCount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    int32 Value;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    EItemType ItemType;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
    int32 CurrentStackCount;


    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Item")
    bool CanStack(const UItem* OtherItem) const;
    virtual bool CanStack_Implementation(const UItem* OtherItem) const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Item")
    bool CanUse() const;
    virtual bool CanUse_Implementation() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Item")
    bool CanEquip() const;
    virtual bool CanEquip_Implementation() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Item")
    bool Use(AActor* User);
    virtual bool Use_Implementation(AActor* User);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Item")
    bool Equip(AActor* Owner);
    virtual bool Equip_Implementation(AActor* Owner);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Item")
    bool Unequip(AActor* Owner);
    virtual bool Unequip_Implementation(AActor* Owner);


    UFUNCTION(BlueprintCallable, Category = "Item")
    void AddToStack(int32 Amount);

    UFUNCTION(BlueprintCallable, Category = "Item")
    bool RemoveFromStack(int32 Amount);

    //ItemID for identifying items or dev tests
    UFUNCTION(BlueprintCallable, Category = "Item")
    FString GetItemID() const;
};