#pragma once

class UItem;
class UInventory;

//Notes TODO: delete this note later
//Delegate, dynamic (can use w/ blueprints), multi (multiple listeners), two param
//Naming either F(delegate/struct)<name> or <name>Delegate(old)|Signature(def)
class InventoryDelegate;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemAddedSignature, UInventory*, Inventory, UItem*, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemRemovedSignature, UInventory*, Inventory, UItem*, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemUsedSignature, UInventory*, Inventory, UItem*, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemEquippedSignature, UInventory*, Inventory, UItem*, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemUnequippedSignature, UInventory*, Inventory, UItem*, Item);