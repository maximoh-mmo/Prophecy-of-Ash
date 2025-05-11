#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "MiscItem.generated.h"

//This is for an Item that you can't do anything with
UCLASS(BlueprintType, Blueprintable)
class YOUR_API UMiscItem : public UItem
{
	GENERATED_BODY()

public:
	UMiscItem();
	
	
	virtual bool CanUse_Implementation() const override;
	virtual bool CanEquip_Implementation() const override;
};