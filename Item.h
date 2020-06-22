#ifndef ITEM_H
#define ITEM_H

#include "Draw.h"
#include "Character.h"

/* Declaring the derived class constructors in the header file and then define them in the cpp file gave an error.
   This unncessarily uses several lines of code that could be saved anyway. Now the constructors are defined in the header file.
   With inherited classes, making an object list for each object of a class was also giving an error.
   And declaring empty deconstructors also gave an error. I had to define the deconstructor (empty brackets) rather than declare it to resolve this.*/

/****************************************************************************************************/
class Item {

public:
	Item(const char* asset, const char* name, const char* description, int worth, int rarity)
	{
		//Item::objList.push_back(this);

		item_asset = asset;
		item_name = name;
		item_description = description;
		item_worth = worth;
		item_rarity = rarity;

		tex = TextureManager::LoadTexture(item_asset);

		//src.x = src.y = 0; src.w = w; src.h = h;
		//dest.x = x; dest.y = y; dest.w = w * dest_rect_mult; dest.h = h * dest_rect_mult;
	}
	~Item() {}

	//static std::vector<Item*> getAllObjects();
	const char* getItemAsset();
	const char* getItemName();
	const char* getItemDescription();
	int getItemWorth();
	int getItemRarity();
	int getItemWidth();
	int getItemHeight();
	int getItemDestRectMult();

protected: // Only derived classes inherit and can access these.
	SDL_Texture* tex;

private:
	//static std::vector<Item*> objList; // list of all objects of this class

	const char* item_asset;
	const char* item_name;
	const char* item_description;

	int item_worth;
	int item_rarity;

	const int item_w = 24; // Play with these numbers. All items should have the same sized icons.
	const int item_h = 24;
	const int item_dest_rect_mult = 1;

	//SDL_Rect src, dest;
};

	/****************************************************************************************************/
	class InventoryItem : public Item {

	public:
		InventoryItem(int inv_slot, int max_stacks, // InventoryItem
					  const char* asset, const char* name, const char* description, int worth, int rarity) // Item
					  : Item{ asset, name, description, worth, rarity } 
		{
			//InventoryItem::objList.push_back(this);

			inventory_slot = inv_slot;
			inventory_max_stacks = max_stacks;
		}
		~InventoryItem() {}

		//static std::vector<InventoryItem*> getAllObjects();
		int getInventorySlot();
		int getMaxStacks();
		void SellItem();

	private:
		//static std::vector<InventoryItem*> objList; // list of all objects of this class

		int inventory_slot;
		int inventory_max_stacks;
	};

		/****************************************************************************************************/
		class CraftingItem : public InventoryItem {

		public:
			CraftingItem(std::vector<const char*> usable_skills, // CraftingItem
						 int inv_slot, int max_stacks, // InventoryItem
						 const char* asset, const char* name, const char* description, int worth, int rarity) // Item
						 : InventoryItem{ inv_slot, max_stacks, asset, name, description, worth, rarity } 
			{
				//CraftingItem::objList.push_back(this);

				skills = usable_skills;

				crafting_item_phrase = "Crafting Item";
			}
			~CraftingItem() {}

			//static std::vector<CraftingItem*> getAllObjects();
			std::vector<const char*> getUsableSkills();

		private:
			//static std::vector<CraftingItem*> objList; // list of all objects of this class

			std::vector<const char*> skills;
			const char* crafting_item_phrase;
		};

		/****************************************************************************************************/
		class Consumable : public InventoryItem {

		public:
			Consumable(const char* use_description, // Consumable
					   int inv_slot, int max_stacks, // InventoryItem
					   const char* asset, const char* name, const char* description, int worth, int rarity) // Item
					   : InventoryItem{ inv_slot, max_stacks, asset, name, description, worth, rarity } 
			{
				//Consumable::objList.push_back(this);

				consumable_description = use_description;
			}
			~Consumable() {}

			//static std::vector<Consumable*> getAllObjects();
			const char* getConsumableDescription();
			void UseConsumable();

		private:
			//static std::vector<Consumable*> objList; // list of all objects of this class

			const char* consumable_description;
		};

			/****************************************************************************************************/
			class Equiptable : public Consumable {

			public:
				Equiptable(int min_lvl, double durab, // Equiptable
						   const char* use_description, // Consumable
						   int inv_slot, int max_stacks, // InventoryItem
						   const char* asset, const char* name, const char* description, int worth, int rarity) // Item
						   : Consumable{ use_description, inv_slot, max_stacks, asset, name, description, worth, rarity } 
				{
					//Equiptable::objList.push_back(this);

					lvl_req = min_lvl;
					durability = durab;

					equiptable_item_phrase = "Equiptable";
				}
				~Equiptable() {}

				//static std::vector<Equiptable*> getAllObjects();
				int getLvlReq();
				double getDurability();
				void EquiptItem();

			private:
				//static std::vector<Equiptable*> objList; // list of all objects of this class

				int lvl_req;
				double durability;
				const char* equiptable_item_phrase;

			};

			/****************************************************************************************************/
			class StorageItem : public Consumable {

			public:
				StorageItem(int num_inv, // StorageItem
							const char* use_description, // Consumable
							int inv_slot, int max_stacks, // InventoryItem
							const char* asset, const char* name, const char* description, int worth, int rarity) // Item
							: Consumable{ use_description, inv_slot, max_stacks, asset, name, description, worth, rarity }
				{
					//StorageItem::objList.push_back(this);

					num_inv_slots = num_inv;

					storage_item_phrase = "Storage";
				}
				~StorageItem() {}

				//static std::vector<StorageItem*> getAllObjects();
				int getNumInvSlots();
				void EquiptStorageItem();

			private:
				//static std::vector<StorageItem*> objList; // list of all objects of this class

				int num_inv_slots;
				const char* storage_item_phrase;

			};

			/****************************************************************************************************/
			class TimedUse : public Consumable {

			public:
				TimedUse(double time, // TimedUse
						 const char* use_description, // Consumable
						 int inv_slot, int max_stacks, // InventoryItem
						 const char* asset, const char* name, const char* description, int worth, int rarity) // Item
						 : Consumable{ use_description, inv_slot, max_stacks, asset, name, description, worth, rarity }
				{
					//TimedUse::objList.push_back(this);

					cast_time = time;

				}
				~TimedUse() {}

				//static std::vector<TimedUse*> getAllObjects();
				double getCastTime();
				void UseItem();

			private:
				//static std::vector<TimedUse*> objList; // list of all objects of this class

				double cast_time;

			};

	/****************************************************************************************************/
	class EquiptedItem : public Item {

	public:
		EquiptedItem(int min_lvl, double durab, // EquiptedItem
					 const char* asset, const char* name, const char* description, int worth, int rarity) // Item
					 : Item{ asset, name, description, worth, rarity } 
		{
			//EquiptedItem::objList.push_back(this);

			lvl_req = min_lvl;
			durability = durab;

			equipted_item_phrase = "Equipted";
		}
		~EquiptedItem() {}

		//static std::vector<EquiptedItem*> getAllObjects();
		int getLvlReq();
		double getDurability();
		void UnequiptItem(); // Destroy the EquiptedItem instance and create a new Equiptable instance (derived from InventoryItem).

	private:
		//static std::vector<EquiptedItem*> objList; // list of all objects of this class

		int lvl_req;
		double durability;
		const char* equipted_item_phrase;
	};

		/****************************************************************************************************/
		class Weapon : public EquiptedItem {

		public:
			Weapon(double dmg, // Weapon
				   int min_lvl, double durab, // EquiptedItem
				   const char* asset, const char* name, const char* description, int worth, int rarity) // Item
				   : EquiptedItem{ min_lvl, durab, asset, name, description, worth, rarity }
			{
				//Weapon::objList.push_back(this);

				base_dmg = dmg;

			}
			~Weapon() {}

			//static std::vector<Weapon*> getAllObjects();
			double getBaseDmg();

		private:
			//static std::vector<Weapon*> objList; // list of all objects of this class

			double base_dmg;
		};

		/****************************************************************************************************/
		class Armor : public EquiptedItem {

		public:
			Armor(double armor, // Armor
				  int min_lvl, double durab, // EquiptedItem
				  const char* asset, const char* name, const char* description, int worth, int rarity) // Item
				  : EquiptedItem{ min_lvl, durab, asset, name, description, worth, rarity }
			{
				//Armor::objList.push_back(this);

				base_armor = armor;

			}
			~Armor() {}

			//static std::vector<Armor*> getAllObjects();
			double getBaseArmor();

		private:
			//static std::vector<Armor*> objList; // list of all objects of this class

			double base_armor;
		};

/****************************************************************************************************/
#endif /* ITEM_H */