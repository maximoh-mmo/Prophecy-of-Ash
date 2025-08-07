#pragma once

#include "CoreMinimal.h"
#include "POA_Item.h"
#include "MiscItem.generated.h"

//This is for an Item that you can't do anything with
UCLASS(BlueprintType, Blueprintable)
class PROPHECYOFASH_API AMiscItem : public APOA_Item
{
	GENERATED_BODY()

public:
	AMiscItem();
	
	
	virtual bool CanUse_Implementation() const override;
	virtual bool CanEquip_Implementation() const override;
};