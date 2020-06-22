#include "Item.h"

/****************************************************************************************************/
// Item (Base Class)
/****************************************************************************************************/

/* The item class will consist of every item in the game that the player can store in their storage inventory or equipted inventory. For items stored in the inventory, 
   they will be able to use (Consumable derived class - instance is destroyed), sell (instance is destroyed), pick up (instance is created), and drop items (instance destroyed).
   They will also be able to buy items (an InventoryItem is created).

   An item icon should be displayed when the player's inventory (InventoryItem) or character menu (EquiptedItem) is displayed that tells the player what it is. 
   If you hover over the item, the name will appear. Left clicking will display its description and worth (and its use if it has one). 
   Right clicking will use the item (if it is a Consumable) or unequipt the item (if it is an EquiptedItem).*/

/****************************************************************************************************/
const char* Item::getItemAsset() { return item_asset; }
const char* Item::getItemName() { return item_name; }
const char* Item::getItemDescription() { return item_description; }
int Item::getItemWorth() { return item_worth; }
int Item::getItemRarity() { return item_rarity; }
int Item::getItemWidth() { return item_w; }
int Item::getItemHeight() { return item_h; }
int Item::getItemDestRectMult() { return item_dest_rect_mult; }
//std::vector<Item*> Item::getAllObjects() { return objList; }
/****************************************************************************************************/

/****************************************************************************************************/
// InventoryItem (Derived Class - from Item)
/****************************************************************************************************/

/* Each InventoryItem has a unique location (slot) in the inventory, which is given by an integer member variable.*/

/****************************************************************************************************/
int InventoryItem::getInventorySlot() { return inventory_slot; }
int InventoryItem::getMaxStacks() { return inventory_max_stacks; }
//std::vector<InventoryItem*> InventoryItem::getAllObjects() { return objList; }
/****************************************************************************************************/

/****************************************************************************************************/
// CraftingItem (Derived Class - from Item --> InventoryItem)
/****************************************************************************************************/

/* CraftingItems cannot be used by right clicking, but contain information on what skills can use it and how. 
   Also designated by a "Crafting Item" phrase. */

/****************************************************************************************************/
std::vector<const char*> CraftingItem::getUsableSkills() { return skills; }
//std::vector<CraftingItem*> CraftingItem::getAllObjects() { return objList; }
/****************************************************************************************************/

/****************************************************************************************************/
// Consumable (Derived Class - from Item --> InventoryItem)
/****************************************************************************************************/

/* Consumable items perform an action when right clicked. They cannot be used in combat.*/

/****************************************************************************************************/
const char* Consumable::getConsumableDescription() { return consumable_description; }
//std::vector<Consumable*> Consumable::getAllObjects() { return objList; }
/****************************************************************************************************/

/****************************************************************************************************/
// Equiptable (Derived Class - from Item --> InventoryItem --> Consumable)
/****************************************************************************************************/

/* Equiptable items get destroyed when equipting and an EquiptedItem gets created. */

/****************************************************************************************************/
int Equiptable::getLvlReq() { return lvl_req; }
double Equiptable::getDurability() { return durability; }
//std::vector<Equiptable*> Equiptable::getAllObjects() { return objList; }
/****************************************************************************************************/

/****************************************************************************************************/
// StorageItem (Derived Class - from Item --> InventoryItem --> Consumable)
/****************************************************************************************************/

/* StorageItems get destroyed when activated and an Inventory gets created. The existing Inventory gets destroyed
   and a StorageItem gets created to take it's place.*/

/****************************************************************************************************/
int StorageItem::getNumInvSlots() { return num_inv_slots; }
//std::vector<StorageItem*> StorageItem::getAllObjects() { return objList; }
/****************************************************************************************************/

/****************************************************************************************************/
// TimedUse (Derived Class - from Item --> InventoryItem --> Consumable)
/****************************************************************************************************/

/* TimedUse items get destroyed when activated, and an ability is cast that grants effects over time
   or grants and effect at the end of the cast duration. */

/****************************************************************************************************/
double TimedUse::getCastTime() { return cast_time; }
//std::vector<TimedUse*> TimedUse::getAllObjects() { return objList; }
/****************************************************************************************************/

/****************************************************************************************************/
// EquiptedItem (Derived Class - from Item)
/****************************************************************************************************/

/* Each EquiptedItem has a minimum level at which it can be equipted, which is given by an integer member variable
   (the value of which is provided by the Equiptable instance that gets destroyed when an EquiptedItem is created).*/

/****************************************************************************************************/
int EquiptedItem::getLvlReq() { return lvl_req; }
double EquiptedItem::getDurability() { return durability; }
//std::vector<EquiptedItem*> EquiptedItem::getAllObjects() { return objList; }
/****************************************************************************************************/

/****************************************************************************************************/
// Weapon (Derived Class - from Item --> EquiptedItem)
/****************************************************************************************************/

/* Each weapon has a base dmg. */

/****************************************************************************************************/
double Weapon::getBaseDmg() { return base_dmg; }
//std::vector<Weapon*> Weapon::getAllObjects() { return objList; }
/****************************************************************************************************/

/****************************************************************************************************/
// Armor (Derived Class - from Item --> EquiptedItem)
/****************************************************************************************************/

/* Each armor has a base armor. */

/****************************************************************************************************/
double Armor::getBaseArmor() { return base_armor; }
//std::vector<Armor*> Armor::getAllObjects() { return objList; }
/****************************************************************************************************/