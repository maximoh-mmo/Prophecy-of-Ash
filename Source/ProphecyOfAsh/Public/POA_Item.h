#pragma once

#include "CoreMinimal.h"
#include "POA_Item.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
    Potion  UMETA(DisplayName = "Potion"),
    Weapon  UMETA(DisplayName = "Weapon"),
    Misc    UMETA(DisplayName = "Miscellaneous")
};

UCLASS()
class PROPHECYOFASH_API APOA_Item : public AActor
{
    GENERATED_BODY()

public:
    APOA_Item();

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
    bool CanStack(const APOA_Item* OtherItem) const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Item")
    bool CanUse() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Item")
    bool CanEquip() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Item")
    bool Use(AActor* User);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Item")
    bool Equip(AActor* Actor);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Item")
    bool UnEquip(AActor* Actor);


    UFUNCTION(BlueprintCallable, Category = "Item")
    void AddToStack(int32 Amount);

    UFUNCTION(BlueprintCallable, Category = "Item")
    bool RemoveFromStack(int32 Amount);

    //ItemID for identifying items or dev tests
    UFUNCTION(BlueprintCallable, Category = "Item")
    FString GetItemID() const;
};