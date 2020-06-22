#include "Character.h"
#include "Draw.h"
#include "Enemies.h"
#include "Log.h"

/****************************************************************************************************/
Character::Character(const char* tex_down_1, const char* tex_down_default, const char* tex_down_3,
	                 const char* tex_up_1, const char* tex_up_default, const char* tex_up_3,
	                 const char* tex_left_1, const char* tex_left_default, const char* tex_left_3,
	                 const char* tex_right_1, const char* tex_right_default, const char* tex_right_3,
					 const char* tex_left_2_fishing, const char* tex_left_2_fishing_bubbles1, const char* tex_left_2_fishing_bubbles2,
					 const char* tex_left_2_fishing_catch1, const char* tex_left_2_fishing_catch2,
					 const char* tex_right_2_fishing, const char* tex_right_2_fishing_bubbles1, const char* tex_right_2_fishing_bubbles2,
					 const char* tex_right_2_fishing_catch1, const char* tex_right_2_fishing_catch2,
					 int w_down_1, int w_down_2, int w_down_3, int w_up_1, int w_up_2, int w_up_3,
					 int w_left_1, int w_left_2, int w_left_3, int w_right_1, int w_right_2, int w_right_3,
					 int h_down_1, int h_down_2, int h_down_3, int h_up_1, int h_up_2, int h_up_3,
					 int h_left_1, int h_left_2, int h_left_3, int h_right_1, int h_right_2, int h_right_3,
					 int w_left_2_fishing, int w_right_2_fishing,
					 int h_left_2_fishing, int h_right_2_fishing,
					 int dest_rect_multiple)
{
	objList.push_back(this);

	charTexture_Down_1 = TextureManager::LoadTexture(tex_down_1); charTexture_Down_Default = TextureManager::LoadTexture(tex_down_default);
	charTexture_Down_3 = TextureManager::LoadTexture(tex_down_3); charTexture_Up_1 = TextureManager::LoadTexture(tex_up_1);
	charTexture_Up_Default = TextureManager::LoadTexture(tex_up_default); charTexture_Up_3 = TextureManager::LoadTexture(tex_up_3);
	charTexture_Left_1 = TextureManager::LoadTexture(tex_left_1); charTexture_Left_Default = TextureManager::LoadTexture(tex_left_default);
	charTexture_Left_3 = TextureManager::LoadTexture(tex_left_3); charTexture_Right_1 = TextureManager::LoadTexture(tex_right_1);
	charTexture_Right_Default = TextureManager::LoadTexture(tex_right_default); charTexture_Right_3 = TextureManager::LoadTexture(tex_right_3);

	charTexture_Left_2_Fishing = TextureManager::LoadTexture(tex_left_2_fishing); charTexture_Left_2_Fishing_Bubbles1 = TextureManager::LoadTexture(tex_left_2_fishing_bubbles1);
	charTexture_Left_2_Fishing_Bubbles2 = TextureManager::LoadTexture(tex_left_2_fishing_bubbles2); charTexture_Left_2_Fishing_Catch1 = TextureManager::LoadTexture(tex_left_2_fishing_catch1);
	charTexture_Left_2_Fishing_Catch2 = TextureManager::LoadTexture(tex_left_2_fishing_catch2); charTexture_Right_2_Fishing = TextureManager::LoadTexture(tex_right_2_fishing);
	charTexture_Right_2_Fishing_Bubbles1 = TextureManager::LoadTexture(tex_right_2_fishing_bubbles1); charTexture_Right_2_Fishing_Bubbles2 = TextureManager::LoadTexture(tex_right_2_fishing_bubbles2);
	charTexture_Right_2_Fishing_Catch1 = TextureManager::LoadTexture(tex_right_2_fishing_catch1); charTexture_Right_2_Fishing_Catch2 = TextureManager::LoadTexture(tex_right_2_fishing_catch2);

	down = true; up = false; left = false; right = false; stand = true;

	inaccessible_area = false;

	Warrior = false; Rogue = false; Predator = false; Mystic = false; Cultist = false; Priest = false;

	health = max_health;
	health_regen_switch = true;

	crit_chance = 0.05;
	crit_dmg_mult = 1.3;

	base_attack_loop = false;
	initialAttack = true;
	initSwitch = true;

	max_inventory = 20;
	inventory = {"Old Fishing Rod"};
	tele_home = {};
	abilities = {};
	exp = 0;

	isFishing = false;
	fish_bite = false;

	// Fish (Fishing) --> catch is the catch chance for each lvl bracket (1-5, 6-10, ..., 46-50). stats are exp_gained, raw_hps, cooked_hps, raw_worth, cooked_worth, rarity
	SkillItem water_hyacinth; water_hyacinth.chance = { 50, 30, 15, 5, 5, 5, 5, 5, 5, 2 };       water_hyacinth.stats = { 0, 0, 0, 0, 0, 0 };      water_hyacinth.name = "Water Hyacinth";
	SkillItem fathead_minnow; fathead_minnow.chance = { 40, 40, 25, 20, 10, 5, 5, 5, 5, 5 };     fathead_minnow.stats = { 2, 5, 8, 2, 3, 1 };      fathead_minnow.name = "Fathead Minnow";
	SkillItem small_bluegill; small_bluegill.chance = { 10, 20, 30, 30, 25, 20, 15, 10, 10, 5 }; small_bluegill.stats = { 4, 7, 10, 5, 6, 1 };     small_bluegill.name = "Small Bluegill";
	SkillItem large_bluegill; large_bluegill.chance = { 0, 10, 20, 30, 30, 25, 20, 15, 15, 10 }; large_bluegill.stats = { 18, 10, 13, 8, 10, 1 };  large_bluegill.name = "Large Bluegill";
	SkillItem silver_perch;   silver_perch.chance =   { 0, 0, 10, 15, 20, 30, 35, 40, 35, 28 };  silver_perch.stats =   { 30, 14, 18, 18, 20, 2 }; silver_perch.name =   "Silver Perch";
	SkillItem gizzard_shad;   gizzard_shad.chance =   { 0, 0, 0, 0, 10, 15, 20, 25, 30, 50 };    gizzard_shad.stats =   { 50, 18, 25, 50, 60, 2 }; gizzard_shad.name =   "Gizzard Shad";

	fish = { water_hyacinth, fathead_minnow, small_bluegill, large_bluegill, silver_perch, gizzard_shad };
	// fish_data contains a vector for each lvl bracket (1-5, 6-10, ..., 46-50) with each entry being a different fish. Used only for catchFish(). Levels 31+ need to be completed
	for (int i = 0; i < SkillItem::num_lvl_brackets; i++)
	{
		std::vector<int> fish_data_row;
		for (int j = 0; j < fish.size(); j++)
			fish_data_row.push_back(fish[j].chance[i]);
		fish_data.push_back(fish_data_row);
	}

	// Ores (Mining) --> stats are exp_gained, worth, min_skill_lvl, rarity.
	SkillItem copper_ore;      copper_ore.stats =      { 4, 4, 1, 1 };        copper_ore.name = "Copper Ore";           copper_ore.min_items =      { "Wooden Pickaxe" };
	SkillItem iron_ore;        iron_ore.stats =        { 8, 6, 6, 1 };        iron_ore.name = "Iron Ore";               iron_ore.min_items =        { "Copper Pickaxe" };
	SkillItem titanium_ore;    titanium_ore.stats =    { 12, 12, 14, 1 };     titanium_ore.name = "Titanium Ore";       titanium_ore.min_items =    { "Iron Pickaxe" }; // Al Alloy = Al + Fe + Cu
	SkillItem emerald_ore;     emerald_ore.stats =     { 20, 80, 22, 2 };     emerald_ore.name = "Emerald Ore";         emerald_ore.min_items =     { "Titanium Alloy Pickaxe" };
	SkillItem coal;            coal.stats =            { 25, 400, 34, 2 };    coal.name = "Coal";                       coal.min_items =            { "Emerald Pickaxe" }; // Ti Alloy = Ti + Al + Fe
	SkillItem gold_ore;        gold_ore.stats =        { 50, 600, 40, 3 };    gold_ore.name = "Gold Ore";               gold_ore.min_items =        { "Steel Pickaxe" }; // Steel = Fe + C
	SkillItem diamond_ore;     diamond_ore.stats =     { 100, 5000, 45, 4 };  diamond_ore.name = "Diamond Ore";         diamond_ore.min_items =     { "Carbon-fiber Pickaxe" }; // Carbon-fiber = ~95% C ore, ~5% Wood
	SkillItem dragonscale_ore; dragonscale_ore.stats = { 250, 40000, 50, 5 }; dragonscale_ore.name = "Dragonscale Ore"; dragonscale_ore.min_items = { "Diamond Pickaxe" };

	ores = { copper_ore, iron_ore, emerald_ore, titanium_ore, coal, gold_ore, diamond_ore, dragonscale_ore };

	// Bars (Smelting) --> stats are exp_gained, worth, min_skill_lvl, rarity.
	SkillItem copper_bar;          copper_bar.stats =          { 4, 14, 1, 1 };       copper_bar.name = "Copper Bar";                 for (int i = 0; i < 3; i++) copper_bar.min_items.push_back("Copper Ore");
	SkillItem iron_bar;            iron_bar.stats =            { 8, 21, 10, 1 };      iron_bar.name = "Iron Bar";                     for (int i = 0; i < 3; i++) iron_bar.min_items.push_back("Iron Ore");
	SkillItem titanium_bar;        titanium_bar.stats =        { 12, 40, 18, 1 };     titanium_bar.name = "Titanium Bar";             for (int i = 0; i < 3; i++) titanium_bar.min_items.push_back("Titanium Ore");
	SkillItem titanium_alloy_bar;  titanium_alloy_bar.stats =  { 16, 240, 22, 2 };    titanium_alloy_bar.name = "Titanium Alloy Bar"; for (int i = 0; i < 4; i++) titanium_alloy_bar.min_items.push_back("Titanium Bar"); for (int i = 0; i < 3; i++) titanium_alloy_bar.min_items.push_back("Iron Bar"); for (int i = 0; i < 2; i++) titanium_alloy_bar.min_items.push_back("Copper Bar");
	SkillItem emerald_bar;         emerald_bar.stats =         { 20, 320, 28, 2 };    emerald_bar.name = "Emerald Bar";               for (int i = 0; i < 3; i++) emerald_bar.min_items.push_back("Emerald Ore");
	SkillItem steel_bar;           steel_bar.stats =           { 40, 1500, 34, 2};    steel_bar.name = "Steel Bar";                   steel_bar.min_items = { "Coal", "Coal", "Coal" }; for (int i = 0; i < 10; i++) steel_bar.min_items.push_back("Iron Bar");
	SkillItem gold_bar;            gold_bar.stats =            { 50, 2000, 40, 3};    gold_bar.name = "Gold Bar";                     gold_bar.min_items = { "Gold Ore", "Gold Ore", "Gold Ore" };
	SkillItem carbon_fiber;        carbon_fiber.stats =        { 80, 9600, 40, 3};    carbon_fiber.name = "Carbon Fiber Bundle";      for (int i = 0; i < 20; i++) carbon_fiber.min_items.push_back("Coal"); for (int i = 0; i < 3; i++) carbon_fiber.min_items.push_back("Wood Log");
	SkillItem diamond_bar;         diamond_bar.stats =         { 100, 16000, 45, 4};  diamond_bar.name = "Diamond Bar";               diamond_bar.min_items = { "Diamond Ore", "Diamond Ore", "Diamond Ore" };
	SkillItem dragonscale_bar;     dragonscale_bar.stats =     { 250, 160000, 50, 5}; dragonscale_bar.name = "Dragonscale Bar";       dragonscale_bar.min_items = { "Dragonscale", "Dragonscale", "Dragonscale" };

	bars = { copper_bar, iron_bar, titanium_bar, titanium_alloy_bar, emerald_bar, steel_bar, gold_bar, carbon_fiber, diamond_bar, dragonscale_bar };

	for (int i = 0; i < 50; i++)
	{
		expThreshold[i] = int(pow((i * 10), 2));
		skillExpThreshold[i] = int(pow((i * 5), 2));
	}

	level = 1;
	gold = 0;
	max_level = 50;
	max_level_status = false;
	max_skill_level = 50;

	blacksmithing_level = 1; armoring_level = 1; smelting_level = 1; mining_level = 1; /* gardening_level = 1; */ herbGathering_level = 1;
	alchemy_level = 1; fishing_level = 1; enchanting_level = 1; fabricWeaving_level = 1; cooking_level = 1;

	blacksmithing_exp = 0; armoring_exp = 0; smelting_exp = 0; mining_exp = 0; /* gardening_exp = 0; */ herbGathering_exp = 0;
	alchemy_exp = 0; fishing_exp = 0; enchanting_exp = 0; fabricWeaving_exp = 0; cooking_exp = 0;

	max_blacksmithing_status = false; max_armoring_status = false; max_smelting_status = false; max_mining_status = false; /* max_gardening_status = false; */ max_herbGathering_status = false;
	max_alchemy_status = false; max_fishing_status = false; max_enchanting_status = false; max_fabricWeaving_status = false; max_cooking_status = false;

	stats_font = TTF_OpenFont("assets/fonts/OpenSans-Regular.ttf", 12);

	health_rect_behind = { 30, 30, bar_width, bar_height };
	stamina_rect_behind = { 30, 30 + bar_height, bar_width, bar_height };
	mana_rect_behind = { 30, 30 + bar_height, bar_width, bar_height };
	health_rect_front = { 30, 30, bar_width, bar_height };
	stamina_rect_front = { 30, 30 + bar_height, bar_width, bar_height };
	mana_rect_front = { 30, 30 + bar_height, bar_width, bar_height };

	srcRect_down_1.w = w_down_1; srcRect_down_2.w = w_down_2; srcRect_down_3.w = w_down_3;
	srcRect_up_1.w = w_up_1; srcRect_up_2.w = w_up_2; srcRect_up_3.w = w_up_3;
	srcRect_left_1.w = w_left_1; srcRect_left_2.w = w_left_2; srcRect_left_3.w = w_left_3;
	srcRect_right_1.w = w_right_1; srcRect_right_2.w = w_right_2; srcRect_right_3.w = w_right_3;
	srcRect_left_2_fishing.w = w_left_2_fishing; srcRect_right_2_fishing.w = w_right_2_fishing;

	srcRect_down_1.h = h_down_1; srcRect_down_2.h = h_down_2; srcRect_down_3.h = h_down_3;
	srcRect_up_1.h = h_up_1; srcRect_up_2.h = h_up_2; srcRect_up_3.h = h_up_3;
	srcRect_left_1.h = h_left_1; srcRect_left_2.h = h_left_2; srcRect_left_3.h = h_left_3;
	srcRect_right_1.h = h_right_1; srcRect_right_2.h = h_right_2; srcRect_right_3.h = h_right_3;
	srcRect_left_2_fishing.h = h_left_2_fishing; srcRect_right_2_fishing.h = h_right_2_fishing;

	destRect_down_1.w = w_down_1 * dest_rect_multiple; destRect_down_2.w = w_down_2 * dest_rect_multiple; destRect_down_3.w = w_down_3 * dest_rect_multiple;
	destRect_up_1.w = w_up_1 * dest_rect_multiple; destRect_up_2.w = w_up_2 * dest_rect_multiple; destRect_up_3.w = w_up_3 * dest_rect_multiple;
	destRect_left_1.w = w_left_1 * dest_rect_multiple; destRect_left_2.w = w_left_2 * dest_rect_multiple; destRect_left_3.w = w_left_3 * dest_rect_multiple;
	destRect_right_1.w = w_right_1 * dest_rect_multiple; destRect_right_2.w = w_right_2 * dest_rect_multiple; destRect_right_3.w = w_right_3 * dest_rect_multiple;
	destRect_left_2_fishing.w = w_left_2_fishing * dest_rect_multiple; destRect_right_2_fishing.w = w_right_2_fishing * dest_rect_multiple;

	destRect_down_1.h = h_down_1 * dest_rect_multiple; destRect_down_2.h = h_down_2 * dest_rect_multiple; destRect_down_3.h = h_down_3 * dest_rect_multiple;
	destRect_up_1.h = h_up_1 * dest_rect_multiple; destRect_up_2.h = h_up_2 * dest_rect_multiple; destRect_up_3.h = h_up_3 * dest_rect_multiple;
	destRect_left_1.h = h_left_1 * dest_rect_multiple; destRect_left_2.h = h_left_2 * dest_rect_multiple; destRect_left_3.h = h_left_3 * dest_rect_multiple;
	destRect_right_1.h = h_right_1 * dest_rect_multiple; destRect_right_2.h = h_right_2 * dest_rect_multiple; destRect_right_3.h = h_right_3 * dest_rect_multiple;
	destRect_left_2_fishing.h = h_left_2_fishing * dest_rect_multiple; destRect_right_2_fishing.h = h_right_2_fishing * dest_rect_multiple;

	xpos = (Game::screenWidth / 2) - (destRect_down_2.w / 2); // Centered on the screen
	ypos = (Game::screenHeight / 2) - (destRect_down_2.h / 2);

	srcRect_down_1.x = srcRect_down_2.x = srcRect_down_3.x = 0;
	srcRect_up_1.x = srcRect_up_2.x = srcRect_up_3.x = 0;
	srcRect_left_1.x = srcRect_left_2.x = srcRect_left_3.x = 0;
	srcRect_right_1.x = srcRect_right_2.x = srcRect_right_3.x = 0;
	srcRect_left_2_fishing.x = srcRect_right_2_fishing.x = 0;

	srcRect_down_1.y = srcRect_down_2.y = srcRect_down_3.y = 0;
	srcRect_up_1.y = srcRect_up_2.y = srcRect_up_3.y = 0;
	srcRect_left_1.y = srcRect_left_2.y = srcRect_left_3.y = 0;
	srcRect_right_1.y = srcRect_right_2.y = srcRect_right_3.y = 0;
	srcRect_left_2_fishing.y = srcRect_right_2_fishing.y = 0;

	destRect_down_1.x = destRect_down_2.x = destRect_down_3.x = xpos;
	destRect_up_1.x = destRect_up_2.x = destRect_up_3.x = xpos;
	destRect_left_1.x = destRect_left_2.x = destRect_left_3.x = xpos;
	destRect_right_1.x = destRect_right_2.x = destRect_right_3.x = xpos;
	destRect_left_2_fishing.x = xpos - (destRect_left_2_fishing.w - destRect_left_2.w); // Keeping player in the same location on screen.
	destRect_right_2_fishing.x = xpos;

	destRect_down_1.y = destRect_down_2.y = destRect_down_3.y = ypos;
	destRect_up_1.y = destRect_up_2.y = destRect_up_3.y = ypos;
	destRect_left_1.y = destRect_left_2.y = destRect_left_3.y = ypos;
	destRect_right_1.y = destRect_right_2.y = destRect_right_3.y = ypos;
	destRect_left_2_fishing.y = destRect_right_2_fishing.y = ypos;
}

/****************************************************************************************************/
void Character::Update()
{
	// Moving the background behind player
	for (int i = 0; i < Map::getAllObjects().size(); i++) // just map object
	{
		if (!stand)
		{
			if (up)
			{
				if ((!isFishing) and (!SDL_RectEquals(&current_destRect, &destRect_left_2_fishing))) // Fixed left-facing fishing bug where player would get stuck in inaccessible areas.
				{
					Map::getAllObjects()[i]->map_y += max_vel; // Map's ypos measured from top left corner of total map.
					if (!inaccessible_area)
					{
						MapObject::MoveObjectsDown(max_vel);
						Enemy::MoveObjectsDown(max_vel);
					}
					for (int j = 0; j < Map::getAllObjects()[i]->inaccessible_segments_y.size(); j++)
					{
						Map::getAllObjects()[i]->inaccessible_segment_centers_y[j] += max_vel;
						for (int k = 0; k < Map::getAllObjects()[i]->inaccessible_segments_y[j].size(); k++)
						{
							Map::getAllObjects()[i]->inaccessible_segments_y[j][k] += max_vel;
						}
					}
				}
			}
			else if (down)
			{
				if ((!isFishing) and (!SDL_RectEquals(&current_destRect, &destRect_left_2_fishing))) // Fixed left-facing fishing bug where player would get stuck in inaccessible areas.
				{
					Map::getAllObjects()[i]->map_y -= max_vel;
					if (!inaccessible_area)
					{
						MapObject::MoveObjectsUp(max_vel);
						Enemy::MoveObjectsUp(max_vel);
					}
					for (int j = 0; j < Map::getAllObjects()[i]->inaccessible_segments_y.size(); j++)
					{
						Map::getAllObjects()[i]->inaccessible_segment_centers_y[j] -= max_vel;
						for (int k = 0; k < Map::getAllObjects()[i]->inaccessible_segments_y[j].size(); k++)
						{
							Map::getAllObjects()[i]->inaccessible_segments_y[j][k] -= max_vel;
						}
					}
				}
			}
			else if (left)
			{
				if ((!isFishing) and (!SDL_RectEquals(&current_destRect, &destRect_left_2_fishing))) // Fixed left-facing fishing bug where player would get stuck in inaccessible areas.
				{
					Map::getAllObjects()[i]->map_x += max_vel;
					if (!inaccessible_area)
					{
						MapObject::MoveObjectsRight(max_vel);
						Enemy::MoveObjectsRight(max_vel);
					}
					for (int j = 0; j < Map::getAllObjects()[i]->inaccessible_segments_x.size(); j++)
					{
						Map::getAllObjects()[i]->inaccessible_segment_centers_x[j] += max_vel;
						for (int k = 0; k < Map::getAllObjects()[i]->inaccessible_segments_x[j].size(); k++)
						{
							Map::getAllObjects()[i]->inaccessible_segments_x[j][k] += max_vel;
						}
					}
				}
			}
			else if (right)
			{
				Map::getAllObjects()[i]->map_x -= max_vel;
				if (!inaccessible_area)
				{
					MapObject::MoveObjectsLeft(max_vel);
					Enemy::MoveObjectsLeft(max_vel);
				}
				for (int j = 0; j < Map::getAllObjects()[i]->inaccessible_segments_x.size(); j++)
				{
					Map::getAllObjects()[i]->inaccessible_segment_centers_x[j] -= max_vel;
					for (int k = 0; k < Map::getAllObjects()[i]->inaccessible_segments_x[j].size(); k++)
					{
						Map::getAllObjects()[i]->inaccessible_segments_x[j][k] -= max_vel;
					}
				}
			}

			// For each vector of x coordinates of one inaccessible segment, for each column, if player is within min and max inaccessible y coords, move back.
			int t = 0;
			int dist_from_center;
			inaccessible_area = false;
			for (std::vector<int> inaccessible_segment_x : Map::getAllObjects()[i]->inaccessible_segments_x)
			{
				dist_from_center = sqrt(pow(Map::getAllObjects()[i]->inaccessible_segment_centers_x[t] - (xpos + (current_destRect.w / 2)), 2) + pow(Map::getAllObjects()[i]->inaccessible_segment_centers_y[t] - (ypos + (current_destRect.h / 2)), 2));
				if (dist_from_center <= Map::getAllObjects()[i]->inaccessible_segment_radii[t])
				{
					for (int j = *min_element(inaccessible_segment_x.begin(), inaccessible_segment_x.end()); j <= *max_element(inaccessible_segment_x.begin(), inaccessible_segment_x.end()); j = j + Map::getAllObjects()[i]->tile_size)
					{
						auto min_itr = std::find(inaccessible_segment_x.begin(), inaccessible_segment_x.end(), j);
						int min_index = std::distance(inaccessible_segment_x.begin(), min_itr);

						auto max_itr = std::find(inaccessible_segment_x.rbegin(), inaccessible_segment_x.rend(), j);
						int max_index = inaccessible_segment_x.rend() - max_itr - 1;

						// Getting the min y values because the index is found for the first occurrence of j, which is the highest x of every column.
						int y_min = Map::getAllObjects()[i]->inaccessible_segments_y[t][min_index];

						// Getting the max y values because the index is now found for the last occurrence of j, which is the lowest x of every column.
						int y_max = Map::getAllObjects()[i]->inaccessible_segments_y[t][max_index];

						// Must be within the column. Note: the bottom boundary condition is off by one tile size, so need to correct for this. 
						if ((ypos + destRect_down_2.h > y_min)& (ypos + destRect_down_2.h - Map::getAllObjects()[i]->tile_size < y_max)& (xpos + destRect_right_2.w > j)& (xpos < j + 1))
						{
							// Revert to original positions of map, inaccessible segment coords, enemies, enemy containment boxes etc.
							inaccessible_area = true;
							inaccessible_tile_type = Map::getAllObjects()[i]->inaccessible_tile_types[t];
							if (up)
							{
								Map::getAllObjects()[i]->map_y -= max_vel;
								for (int k = 0; k < Map::getAllObjects()[i]->inaccessible_segments_y.size(); k++)
								{
									for (int l = 0; l < Map::getAllObjects()[i]->inaccessible_segments_y[k].size(); l++)
									{
										Map::getAllObjects()[i]->inaccessible_segments_y[k][l] -= max_vel;
									}
								}
								for (int m = 0; m < Map::getAllObjects()[i]->inaccessible_segment_centers_y.size(); m++)
								{
									Map::getAllObjects()[i]->inaccessible_segment_centers_y[m] -= max_vel;
								}
							}
							else if (down)
							{
								Map::getAllObjects()[i]->map_y += max_vel;
								for (int k = 0; k < Map::getAllObjects()[i]->inaccessible_segments_y.size(); k++)
								{
									for (int l = 0; l < Map::getAllObjects()[i]->inaccessible_segments_y[k].size(); l++)
									{
										Map::getAllObjects()[i]->inaccessible_segments_y[k][l] += max_vel;
									}
								}
								for (int m = 0; m < Map::getAllObjects()[i]->inaccessible_segment_centers_y.size(); m++)
								{
									Map::getAllObjects()[i]->inaccessible_segment_centers_y[m] += max_vel;
								}
							}
							else if (left)
							{
								Map::getAllObjects()[i]->map_x -= max_vel;
								for (int k = 0; k < Map::getAllObjects()[i]->inaccessible_segments_x.size(); k++)
								{
									for (int l = 0; l < Map::getAllObjects()[i]->inaccessible_segments_x[k].size(); l++)
									{
										Map::getAllObjects()[i]->inaccessible_segments_x[k][l] -= max_vel;
									}
								}
								for (int m = 0; m < Map::getAllObjects()[i]->inaccessible_segment_centers_x.size(); m++)
								{
									Map::getAllObjects()[i]->inaccessible_segment_centers_x[m] -= max_vel;
								}
							}
							else if (right)
							{
								Map::getAllObjects()[i]->map_x += max_vel;
								for (int k = 0; k < Map::getAllObjects()[i]->inaccessible_segments_x.size(); k++)
								{
									for (int l = 0; l < Map::getAllObjects()[i]->inaccessible_segments_x[k].size(); l++)
									{
										Map::getAllObjects()[i]->inaccessible_segments_x[k][l] += max_vel;
									}
								}
								for (int m = 0; m < Map::getAllObjects()[i]->inaccessible_segment_centers_x.size(); m++)
								{
									Map::getAllObjects()[i]->inaccessible_segment_centers_x[m] += max_vel;
								}
							}
						}
					}
				}
				t++;
			}
		}
	}

	// Fishing
	if (isFishing)
		Fishing();

	// Base attack on Enemy
	if (Enemy::AnyHighlighted(true, false)) // if any enemies are attack_highlighted, perform base attack once close enough
		baseAttack(Enemy::AttackHighlightedEnemy());

	// Updating health, stamina, mana bars
	health_rect_front = { 30, 30, int(round(bar_width * health / max_health)), bar_height };
	if ((Warrior == true) | (Rogue == true) | (Predator == true))
	{
		stamina_rect_front = { 30, 30 + bar_height, int(round(bar_width * stamina / max_stamina)), bar_height };
	}
	else
	{
		mana_rect_front = { 30, 30 + bar_height, int(round(bar_width * mana / max_mana)), bar_height };
	}

	// Regenerating health, stamina, mana
	if (health_regen_switch)
	{
		health_regen_timer = SDL_AddTimer(10000, healthRegen_callback, NULL); // Every 10 seconds regen 1% max health
		health_regen_switch = false;
	}
	if ((Warrior == true) | (Rogue == true) | (Predator == true))
	{
		if (stamina_regen_switch)
		{
			stamina_regen_timer = SDL_AddTimer(1000, staminaRegen_callback, NULL);
			stamina_regen_switch = false;
		}
	}
	else
	{
		if (mana_regen_switch)
		{
			mana_regen_timer = SDL_AddTimer(5000, manaRegen_callback, NULL);
			mana_regen_switch = false;
		}
	}
}

/****************************************************************************************************/
void Character::Render()
{
	if (up)
	{
		if (!stand)
		{
			current_destRect = Animate(charTexture_Up_1, charTexture_Up_Default, charTexture_Up_3);
			interruptFishing();
		}
		else
		{
			SDL_RenderCopy(Game::renderer, charTexture_Up_Default, &srcRect_up_2, &destRect_up_2);
			frame = 0;
			current_destRect = destRect_up_2;
		}
	}
	else if (down)
	{
		if (!stand)
		{
			current_destRect = Animate(charTexture_Down_1, charTexture_Down_Default, charTexture_Down_3);
			interruptFishing();
		}
		else
		{
			SDL_RenderCopy(Game::renderer, charTexture_Down_Default, &srcRect_down_2, &destRect_down_2);
			frame = 0;
			current_destRect = destRect_down_2;
		}
	}
	else if (left)
	{
		if (!stand)
		{
			current_destRect = Animate(charTexture_Left_1, charTexture_Left_Default, charTexture_Left_3);
			interruptFishing();
		}
		else
		{
			if (isFishing)
			{
				if (fish_bite)
				{
					Fish_Bite_Animate(charTexture_Left_2_Fishing_Catch1, charTexture_Left_2_Fishing_Catch2);
				}
				else
				{
					Fishing_Animate(charTexture_Left_2_Fishing_Bubbles1, charTexture_Left_2_Fishing, charTexture_Left_2_Fishing_Bubbles2);
				}
			}
			else
			{
				SDL_RenderCopy(Game::renderer, charTexture_Left_Default, &srcRect_left_2, &destRect_left_2);
				current_destRect = destRect_left_2;
			}
			frame = 0;
		}
	}
	else if (right)
	{
		if (!stand)
		{
			current_destRect = Animate(charTexture_Right_1, charTexture_Right_Default, charTexture_Right_3);
			interruptFishing();
		}
		else
		{
			if (isFishing)
			{
				if (fish_bite)
				{
					Fish_Bite_Animate(charTexture_Right_2_Fishing_Catch1, charTexture_Right_2_Fishing_Catch2);
				}
				else
				{
					Fishing_Animate(charTexture_Right_2_Fishing_Bubbles1, charTexture_Right_2_Fishing, charTexture_Right_2_Fishing_Bubbles2);
				}
			}
			else
			{
				SDL_RenderCopy(Game::renderer, charTexture_Right_Default, &srcRect_right_2, &destRect_right_2);
				current_destRect = destRect_right_2;
			}
			frame = 0;
		}
	}

	if (frame / 4 >= walking_frames) // cycle between sprites
	{
		frame = 0;
	}

	if (isFishing)
	{
		if (fish_bite)
		{
			if (fish_bite_frame / 4 >= fish_bite_frames_tot)
			{
				fish_bite_frame = 0;
			}
		}
		else
		{
			if (fishing_frame / 4 >= fishing_frames_tot)
			{
				fishing_frame = 0;
			}
		}
	}

	//DrawHitbox(255, 0, 0, 255); // red

	DrawHealthBar();
	if ((Warrior == true) | (Rogue == true) | (Predator == true))
	{
		DrawStaminaBar();
	}
	else
	{
		DrawManaBar();
	}
}

/****************************************************************************************************/
SDL_Rect Character::Animate(SDL_Texture* tex_1, SDL_Texture* tex_default, SDL_Texture* tex_3)
{
	if (frame < walking_frames)
	{
		if (up)
		{
			SDL_RenderCopy(Game::renderer, tex_1, &srcRect_up_1, &destRect_up_1); // first sprite (leg up)
			frame += 1;
			current_destRect = destRect_up_1;
		}
		else if (down)
		{
			SDL_RenderCopy(Game::renderer, tex_1, &srcRect_down_1, &destRect_down_1); // first sprite (leg up)
			frame += 1;
			current_destRect = destRect_down_1;
		}
		else if (left)
		{
			SDL_RenderCopy(Game::renderer, tex_1, &srcRect_left_1, &destRect_left_1); // first sprite (leg up)
			frame += 1;
			current_destRect = destRect_left_1;
		}
		else if (right)
		{
			SDL_RenderCopy(Game::renderer, tex_1, &srcRect_right_1, &destRect_right_1); // first sprite (leg up)
			frame += 1;
			current_destRect = destRect_right_1;
		}
	}
	else if (((frame >= walking_frames) & (frame < walking_frames * 2)) | ((frame >= walking_frames * 3) & (frame < walking_frames * 4)))
	{
		if (up)
		{
			SDL_RenderCopy(Game::renderer, tex_default, &srcRect_up_2, &destRect_up_2); // second sprite (default)
			frame += 1;
			current_destRect = destRect_up_2;
		}
		else if (down)
		{
			SDL_RenderCopy(Game::renderer, tex_default, &srcRect_down_2, &destRect_down_2); // second sprite (default)
			frame += 1;
			current_destRect = destRect_down_2;
		}
		else if (left)
		{
			SDL_RenderCopy(Game::renderer, tex_default, &srcRect_left_2, &destRect_left_2); // second sprite (default)
			frame += 1;
			current_destRect = destRect_left_2;
		}
		else if (right)
		{
			SDL_RenderCopy(Game::renderer, tex_default, &srcRect_right_2, &destRect_right_2); // second sprite (default)
			frame += 1;
			current_destRect = destRect_right_2;
		}
	}
	else if ((frame >= walking_frames * 2) & (frame < walking_frames * 3))
	{
		if (up)
		{
			SDL_RenderCopy(Game::renderer, tex_3, &srcRect_up_3, &destRect_up_3); // third sprite (other leg up)
			frame += 1;
			current_destRect = destRect_up_3;
		}
		else if (down)
		{
			SDL_RenderCopy(Game::renderer, tex_3, &srcRect_down_3, &destRect_down_3); // third sprite (other leg up)
			frame += 1;
			current_destRect = destRect_down_3;
		}
		else if (left)
		{
			SDL_RenderCopy(Game::renderer, tex_3, &srcRect_left_3, &destRect_left_3); // third sprite (other leg up)
			frame += 1;
			current_destRect = destRect_left_3;
		}
		else if (right)
		{
			SDL_RenderCopy(Game::renderer, tex_3, &srcRect_right_3, &destRect_right_3); // third sprite (other leg up)
			frame += 1;
			current_destRect = destRect_right_3;
		}
	}
	return current_destRect;
}

/****************************************************************************************************/
void Character::Fishing_Animate(SDL_Texture* tex_1, SDL_Texture* tex_default, SDL_Texture* tex_2)
{
	if ((fishing_frame < fishing_frames_tot) | ((fishing_frame >= fishing_frames_tot * 2) & (fishing_frame < fishing_frames_tot * 3)))
	{
		if (up)
		{
			/*
			SDL_RenderCopy(Game::renderer, tex_default, &srcRect_up_2_fishing, &destRect_up_2_fishing); // first sprite (default fishing)
			fishing_frame += 1;
			current_destRect = destRect_up_2_fishing;
			*/
		}
		else if (down)
		{
			/*
			SDL_RenderCopy(Game::renderer, tex_default, &srcRect_down_2_fishing, &destRect_down_2_fishing); // first sprite (default fishing)
			fishing_frame += 1;
			current_destRect = destRect_down_2_fishing;
			*/
		}
		else if (left)
		{
			SDL_RenderCopy(Game::renderer, tex_default, &srcRect_left_2_fishing, &destRect_left_2_fishing); // first sprite (default fishing)
			fishing_frame += 1;
			current_destRect = destRect_left_2_fishing;
		}
		else if (right)
		{
			SDL_RenderCopy(Game::renderer, tex_default, &srcRect_right_2_fishing, &destRect_right_2_fishing); // first sprite (default fishing)
			fishing_frame += 1;
			current_destRect = destRect_right_2_fishing;
		}
	}
	else if ((fishing_frame >= fishing_frames_tot) & (fishing_frame < fishing_frames_tot * 2))
	{
		if (up)
		{
			/*
			SDL_RenderCopy(Game::renderer, tex_1, &srcRect_up_2_fishing, &destRect_up_2_fishing); // second sprite (bubble 1)
			fishing_frame += 1;
			current_destRect = destRect_up_2_fishing;
			*/
		}
		else if (down)
		{
			/*
			SDL_RenderCopy(Game::renderer, tex_1, &srcRect_down_2_fishing, &destRect_down_2_fishing); // second sprite (bubble 1)
			fishing_frame += 1;
			current_destRect = destRect_down_2_fishing;
			*/
		}
		else if (left)
		{
			SDL_RenderCopy(Game::renderer, tex_1, &srcRect_left_2_fishing, &destRect_left_2_fishing); // second sprite (bubble 1)
			fishing_frame += 1;
			current_destRect = destRect_left_2_fishing;
		}
		else if (right)
		{
			SDL_RenderCopy(Game::renderer, tex_1, &srcRect_right_2_fishing, &destRect_right_2_fishing); // second sprite (bubble 1)
			fishing_frame += 1;
			current_destRect = destRect_right_2_fishing;
		}
	}
	else if ((fishing_frame >= fishing_frames_tot * 3) & (fishing_frame < fishing_frames_tot * 4))
	{
		if (up)
		{
			/*
			SDL_RenderCopy(Game::renderer, tex_2, &srcRect_up_2_fishing, &destRect_up_2_fishing); // third sprite (bubble 2)
			fishing_frame += 1;
			current_destRect = destRect_up_2_fishing;
			*/
		}
		else if (down)
		{
			/*
			SDL_RenderCopy(Game::renderer, tex_2, &srcRect_down_2_fishing, &destRect_down_2_fishing); // third sprite (bubble 2)
			fishing_frame += 1;
			current_destRect = destRect_down_2_fishing;
			*/
		}
		else if (left)
		{
			SDL_RenderCopy(Game::renderer, tex_2, &srcRect_left_2_fishing, &destRect_left_2_fishing); // third sprite (bubble 2)
			fishing_frame += 1;
			current_destRect = destRect_left_2_fishing;
		}
		else if (right)
		{
			SDL_RenderCopy(Game::renderer, tex_2, &srcRect_right_2_fishing, &destRect_right_2_fishing); // third sprite (bubble 2)
			fishing_frame += 1;
			current_destRect = destRect_right_2_fishing;
		}
	}
}

/****************************************************************************************************/
void Character::Fish_Bite_Animate(SDL_Texture* tex_1, SDL_Texture* tex_2)
{
	if (fish_bite_frame < fish_bite_frames_tot * 2)
	{
		if (up)
		{
			/*
			SDL_RenderCopy(Game::renderer, tex_1, &srcRect_up_2_fishing, &destRect_up_2_fishing); // first sprite (catch 1)
			fish_bite_frame += 1;
			current_destRect = destRect_up_2_fishing;
			*/
		}
		else if (down)
		{
			/*
			SDL_RenderCopy(Game::renderer, tex_1, &srcRect_down_2_fishing, &destRect_down_2_fishing); // first sprite (catch 1)
			fish_bite_frame += 1;
			current_destRect = destRect_down_2_fishing;
			*/
		}
		else if (left)
		{
			SDL_RenderCopy(Game::renderer, tex_1, &srcRect_left_2_fishing, &destRect_left_2_fishing); // first sprite (catch 1)
			fish_bite_frame += 1;
			current_destRect = destRect_left_2_fishing;
		}
		else if (right)
		{
			SDL_RenderCopy(Game::renderer, tex_1, &srcRect_right_2_fishing, &destRect_right_2_fishing); // first sprite (catch 1)
			fish_bite_frame += 1;
			current_destRect = destRect_right_2_fishing;
		}
	}
	else if ((fish_bite_frame >= fish_bite_frames_tot * 2) & (fish_bite_frame < fish_bite_frames_tot * 4))
	{
		if (up)
		{
			/*
			SDL_RenderCopy(Game::renderer, tex_2, &srcRect_up_2_fishing, &destRect_up_2_fishing); // second sprite (catch 2)
			fish_bite_frame += 1;
			current_destRect = destRect_up_2_fishing;
			*/
		}
		else if (down)
		{
			/*
			SDL_RenderCopy(Game::renderer, tex_2, &srcRect_down_2_fishing, &destRect_down_2_fishing); // second sprite (catch 2)
			fish_bite_frame += 1;
			current_destRect = destRect_down_2_fishing;
			*/
		}
		else if (left)
		{
			SDL_RenderCopy(Game::renderer, tex_2, &srcRect_left_2_fishing, &destRect_left_2_fishing); // second sprite (catch 2)
			fish_bite_frame += 1;
			current_destRect = destRect_left_2_fishing;
		}
		else if (right)
		{
			SDL_RenderCopy(Game::renderer, tex_2, &srcRect_right_2_fishing, &destRect_right_2_fishing); // second sprite (catch 2)
			fish_bite_frame += 1;
			current_destRect = destRect_right_2_fishing;
		}
	}
}

/****************************************************************************************************/
void Character::Fishing()
{
	if (fishingLoopCount == 0)
	{
		catch_chance = Game::getRandom();
	}
	if ((fishingLoopTotal >= 1) & (fishingLoopCount < fishingLoopCount_Reset))
	{
		if (catch_chance <= 0.1) // 10% chance to catch a fish each loop
		{
			fish_bite = true;
		}
	}

	fishingLoopCount += 1;
	if (fishingLoopCount >= fishingLoopCount_Reset)
	{
		fishingLoopCount = 0;
		fishingLoopTotal += 1;
		if (fish_bite)
		{
			fishing_frame = 0;
		}
		fish_bite = false;
	}
}

/****************************************************************************************************/
void Character::catchFish()
{
	fish_prob = Game::getRandom();
	int t = (fishing_level - 1) / 5; // Bracket of levels 1-5 (0), 6-10 (1), etc. (e.g. level 43 is in bracket 42 // 5 = 8)
	std::vector<int>::iterator ptr_left = fish_data[t].begin();
	std::vector<int>::iterator ptr_right = fish_data[t].begin();

	for (int i = 0; i < fish_data[t].size(); i++)
	{
		std::advance(ptr_right, 1);
		if ((fish_prob * 100 > std::accumulate(fish_data[t].begin(), ptr_left, 0)) & (fish_prob * 100 <= std::accumulate(fish_data[t].begin(), ptr_right, 0)))
		{
			gainItem(fish[i].name, false);
			for (int j = 0; j < Log::getAllObjects().size(); j++) // just log object
			{
				catch_str = std::string("You caught a ") + std::string(fish[i].name) + std::string("!");
				Log::getAllObjects()[j]->LogStore({catch_str});
			}
			gainSkillExp(fish[i].stats[0], "Fishing");
			break;
		}
		std::advance(ptr_left, 1);
	}
}

/****************************************************************************************************/
void Character::interruptFishing()
{
	fishing_frame = 0;
	fish_bite_frame = 0;
	fishingLoopCount = 0;
	fishingLoopTotal = 0;
	isFishing = false;
	fish_bite = false;
}

/****************************************************************************************************/
void Character::baseAttack(int enemy_int)
{
	double dist = Enemy::getAllObjects()[enemy_int]->DistanceToPlayer();
	if (dist < max_range)
	{
		if (!base_attack_loop)
		{
			if (initialAttack)
			{
				Attack(enemy_int);
				initialAttack = false;
			}
			else
				attack_timer = SDL_AddTimer(2000, attack_callback, Enemy::getAllObjects()[enemy_int]); // After 2 seconds, call attack function for enemy object.

			base_attack_loop = !base_attack_loop; // Acts as a switch to turn off calling the attack function until 2 seconds have passed.
		}
		if (Enemy::getAllObjects()[enemy_int]->threat != 0)
			Enemy::getAllObjects()[enemy_int]->attackLoop = true;
	}
	else
	{
		if (!initialAttack)
		{
			if (initSwitch)
			{
				initAttackCoolDown_timer = SDL_AddTimer(2000, initAttackCoolDown_callback, Enemy::getAllObjects()[enemy_int]); // After 2 seconds, call initAttackCoolDown function for enemy object.
				initSwitch = false; // Prevents repeated calling of initAttackCoolDown
			}
		}
	}
}

/****************************************************************************************************/
void Character::Attack(int enemy_int)
{
	double dodge_rand = Game::getRandom();
	double crit_rand = Game::getRandom();
	double dmg_rand = Game::getRandom();

	int dmg_rand_int = 3; // int between -3 and 3 (+- 30% dmg)
	if (dmg_rand < double(1) / double(7))
		dmg_rand_int = -3;
	else if ((dmg_rand > double(1) / double(7)) & (dmg_rand < double(2) / double(7)))
		dmg_rand_int = -2;
	else if ((dmg_rand > double(2) / double(7)) & (dmg_rand < double(3) / double(7)))
		dmg_rand_int = -1;
	else if ((dmg_rand > double(3) / double(7)) & (dmg_rand < double(4) / double(7)))
		dmg_rand_int = 0;
	else if ((dmg_rand > double(4) / double(7)) & (dmg_rand < double(5) / double(7)))
		dmg_rand_int = 1;
	else if ((dmg_rand > double(5) / double(7)) & (dmg_rand < double(6) / double(7)))
		dmg_rand_int = 2;
	else if ((dmg_rand > double(6) / double(7)))
		dmg_rand_int = 3;

	double dist = Enemy::getAllObjects()[enemy_int]->DistanceToPlayer();
	if (dist < max_range)
	{
		if (Enemy::getAllObjects()[enemy_int]->health > 0)
		{
			if (dodge_rand > Enemy::getAllObjects()[enemy_int]->dodge_chance) // If enemy does not dodge...
			{
				if (crit_rand > crit_chance) // If not a critical hit...
				{
					Enemy::getAllObjects()[enemy_int]->health -= base_dmg + (base_dmg * dmg_rand_int / 10);
					Enemy::getAllObjects()[enemy_int]->health = std::max(double(0), Enemy::getAllObjects()[enemy_int]->health);
					// Add floating damage text above enemy's head
				}
				else // If a critcal hit...
				{
					Enemy::getAllObjects()[enemy_int]->health -= (base_dmg + (base_dmg * dmg_rand_int / 10)) * crit_dmg_mult;
					Enemy::getAllObjects()[enemy_int]->health = std::max(double(0), Enemy::getAllObjects()[enemy_int]->health);
					// Add "critical hit!" text or emphasize the crit with different color
				}
			}
			else // If enemy dodges...
			{
				Enemy::getAllObjects()[enemy_int]->health = std::max(double(0), Enemy::getAllObjects()[enemy_int]->health);
				// Add dodge text above enemy's head

			}
		}
	}
	base_attack_loop = !base_attack_loop;
}

/****************************************************************************************************/
void Character::initAttackCoolDown()
{
	initialAttack = true;
	initSwitch = true;
}

/****************************************************************************************************/
Uint32 Character::attack_callback(Uint32 interval, void* param) // Call attack function after 2 seconds
{
	// Passing "enemy" as param, which is the specific enemy object that is attacking. Need this object to call nonstatic attack function.
	SDL_Event event;

	event.type = SDL_USEREVENT;
	event.user.code = BASE_ATTACK;
	event.user.data1 = param;
	event.user.data2 = NULL;

	SDL_PushEvent(&event);

	return 0; // Only fire once every time this is called. Return interval if repeating.
}

/****************************************************************************************************/
Uint32 Character::initAttackCoolDown_callback(Uint32 interval, void* param) // Call initAttackCoolDown function after 2 seconds
{
	// Passing "this" as param, which is the specific enemy object that is attacking. Need this object to call nonstatic attack function.
	SDL_Event event;

	event.type = SDL_USEREVENT;
	event.user.code = BASE_ATTACK_COOLDOWN;
	event.user.data1 = param;
	event.user.data2 = NULL;

	SDL_PushEvent(&event);

	return 0; // Only fire once every time this is called. Return interval if repeating.
}

/****************************************************************************************************/
void Character::DrawHitbox(int r, int g, int b, int a)
{
	SDL_SetRenderDrawColor(Game::renderer, r, g, b, a); // set render draw color
	SDL_RenderDrawRect(Game::renderer, &current_destRect); // render current frame hitbox
	SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255); // reset render draw color
}

/****************************************************************************************************/
void Character::DrawHealthBar()
{
	TextureManager::DrawFilledBox(health_rect_behind, 200, 0, 0, 255);
	TextureManager::DrawFilledBox(health_rect_front, 0, 200, 0, 255);

	health_str = std::to_string(int(round(100 * health / max_health))) + std::string("%");
	health_char = health_str.c_str();
	health_text = TextureManager::LoadText(stats_font, health_char, { 0,0,0 });
	int health_width; int health_height; TTF_SizeText(stats_font, health_char, &health_width, &health_height);
	health_rect.w = health_width;
	health_rect.h = health_height;
	health_rect.x = 30 + (bar_width / 2) - (health_width / 2);
	health_rect.y = 30 + (bar_height / 2) - (health_height / 2);
	SDL_RenderCopy(Game::renderer, health_text, NULL, &health_rect);
}

/****************************************************************************************************/
void Character::DrawStaminaBar()
{
	TextureManager::DrawFilledBox(stamina_rect_behind, 105, 105, 105, 255);
	TextureManager::DrawFilledBox(stamina_rect_front, 200, 200, 0, 255);

	stamina_str = std::to_string(int(round(100 * stamina / max_stamina))) + std::string("%");
	stamina_char = stamina_str.c_str();
	stamina_text = TextureManager::LoadText(stats_font, stamina_char, { 0,0,0 });
	int stamina_width; int stamina_height; TTF_SizeText(stats_font, stamina_char, &stamina_width, &stamina_height);
	stamina_rect.w = stamina_width;
	stamina_rect.h = stamina_height;
	stamina_rect.x = 30 + (bar_width / 2) - (stamina_width / 2);
	stamina_rect.y = 30 + bar_height + (bar_height / 2) - (stamina_height / 2);
	SDL_RenderCopy(Game::renderer, stamina_text, NULL, &stamina_rect);
}

/****************************************************************************************************/
void Character::DrawManaBar()
{
	TextureManager::DrawFilledBox(mana_rect_behind, 105, 105, 105, 255);
	TextureManager::DrawFilledBox(mana_rect_front, 0, 80, 200, 255);

	mana_str = std::to_string(int(round(100 * mana / max_mana))) + std::string("%");
	mana_char = mana_str.c_str();
	mana_text = TextureManager::LoadText(stats_font, mana_char, { 0,0,0 });
	int mana_width; int mana_height; TTF_SizeText(stats_font, mana_char, &mana_width, &mana_height);
	mana_rect.w = mana_width;
	mana_rect.h = mana_height;
	mana_rect.x = 30 + (bar_width / 2) - (mana_width / 2);
	mana_rect.y = 30 + bar_height + (bar_height / 2) - (mana_height / 2);
	SDL_RenderCopy(Game::renderer, mana_text, NULL, &mana_rect);
}

/****************************************************************************************************/
std::vector<Character*> Character::getAllObjects()
{
	return objList;
}

/****************************************************************************************************/
void Character::gainExp(int gainedExp)
{
	if (!max_level_status)
	{
		exp += gainedExp;
		for (int j = 0; j < Log::getAllObjects().size(); j++) // just log object
		{
			exp_str = std::string("Gained ") + std::to_string(gainedExp) + std::string(" experience.");
			Log::getAllObjects()[j]->LogStore({ exp_str });
		}

		int t = 0;
		for (int i = std::min(level, max_level - 2); i < max_level - 1; i++)
		{
			if ((exp >= expThreshold[std::min(i, max_level - 2)]) & (exp <= expThreshold[std::min(i + 1, max_level - 1)]) & (level != max_level - 1))
			{
				level += 1 + t;
				level = std::min(level, max_level);
				for (int j = 0; j < Log::getAllObjects().size(); j++) // just log object
				{
					level_str = std::string("You are now level ") + std::to_string(level) + std::string(".");
					Log::getAllObjects()[j]->LogStore({ std::string("Congratulations! You\'ve leveled up!"), level_str });
				}
			}
			t += 1;
		}
		if (exp >= expThreshold[max_level - 1])
		{
			for (int j = 0; j < Log::getAllObjects().size(); j++) // just log object
			{
				maxlevel_str = std::string("Congratulations! You\'ve reached the max level, ") + std::to_string(max_level) + std::string("!");
				Log::getAllObjects()[j]->LogStore({ maxlevel_str });
			}
			max_level_status = true;
		}
	}
}

/****************************************************************************************************/
void Character::gainSkillExp(int gainedSkillExp, const char* skill)
{
	int skill_exp = 0;
	int skill_level = 0;
	bool max_skill_status = false;
	if (skill == "Blacksmithing") { skill_exp = blacksmithing_exp; skill_level = blacksmithing_level; max_skill_status = max_blacksmithing_status; }
	else if (skill == "Armoring") { skill_exp = armoring_exp; skill_level = armoring_level; max_skill_status = max_armoring_status; }
	else if (skill == "Smelting") { skill_exp = smelting_exp; skill_level = smelting_level; max_skill_status = max_smelting_status; }
	else if (skill == "Mining") { skill_exp = mining_exp; skill_level = mining_level; max_skill_status = max_mining_status; }
	/* else if (skill == "Gardening") { skill_exp = gardening_exp; skill_level = gardening_level; max_skill_status = max_gardening_status; } */
	else if (skill == "Herb Gathering") { skill_exp = herbGathering_exp; skill_level = herbGathering_level; max_skill_status = max_herbGathering_status; }
	else if (skill == "Alchemy") { skill_exp = alchemy_exp; skill_level = alchemy_level; max_skill_status = max_alchemy_status; }
	else if (skill == "Fishing") { skill_exp = fishing_exp; skill_level = fishing_level; max_skill_status = max_fishing_status; }
	else if (skill == "Enchanting") { skill_exp = enchanting_exp; skill_level = enchanting_level; max_skill_status = max_enchanting_status; }
	else if (skill == "Babric Weaving") { skill_exp = fabricWeaving_exp; skill_level = fabricWeaving_level; max_skill_status = max_fabricWeaving_status; }
	else if (skill == "Cooking") { skill_exp = cooking_exp; skill_level = cooking_level; max_skill_status = max_cooking_status; }

	if (!max_skill_status)
	{
		skill_exp += gainedSkillExp;

		for (int j = 0; j < Log::getAllObjects().size(); j++) // just log object
		{
			skillexp_str = std::string("Gained ") + std::to_string(gainedSkillExp) + std::string(" ") + std::string(skill) + std::string(" experience.");
			Log::getAllObjects()[j]->LogStore({ skillexp_str });
		}

		int t = 0;
		for (int i = std::min(skill_level, max_skill_level - 2); i < max_skill_level - 1; i++)
		{
			if ((skill_exp >= skillExpThreshold[std::min(i, max_skill_level - 2)]) & (skill_exp <= skillExpThreshold[std::min(i + 1, max_skill_level - 1)]) & (skill_level != max_skill_level - 1))
			{
				skill_level += 1 + t;
				skill_level = std::min(skill_level, max_skill_level);

				for (int j = 0; j < Log::getAllObjects().size(); j++) // just log object
				{
					skilllevel_str = std::string("Congratulations! You are now level ") + std::to_string(skill_level) + std::string(" in ") + std::string(skill) + std::string("!");
					Log::getAllObjects()[j]->LogStore({ skilllevel_str });
				}
			}
			t += 1;
		}
		if (skill_exp >= skillExpThreshold[max_skill_level - 1])
		{
			for (int j = 0; j < Log::getAllObjects().size(); j++) // just log object
			{
				skillmaxlevel_str = std::string("Congratulations! You\'ve reached the max level, ") + std::to_string(max_skill_level) + std::string(", in ") + std::string(skill) + std::string("!");
				Log::getAllObjects()[j]->LogStore({ skillmaxlevel_str });
			}
			max_skill_status = true;
		}

		if (skill == "Blacksmithing") { blacksmithing_exp = skill_exp; blacksmithing_level = skill_level; max_blacksmithing_status = max_skill_status; }
		else if (skill == "Armoring") { armoring_exp = skill_exp; armoring_level = skill_level; max_armoring_status = max_skill_status; }
		else if (skill == "Smelting") { smelting_exp = skill_exp; smelting_level = skill_level; max_smelting_status = max_skill_status; }
		else if (skill == "Mining") { mining_exp = skill_exp; mining_level = skill_level; max_mining_status = max_skill_status; }
		/* else if (skill == "Gardening") { gardening_exp = skill_exp; gardening_level = skill_level; max_gardening_status = max_skill_status; } */
		else if (skill == "Herb Gathering") { herbGathering_exp = skill_exp; herbGathering_level = skill_level; max_herbGathering_status = max_skill_status; }
		else if (skill == "Alchemy") { alchemy_exp = skill_exp; alchemy_level = skill_level; max_alchemy_status = max_skill_status; }
		else if (skill == "Fishing") { fishing_exp = skill_exp; fishing_level = skill_level; max_fishing_status = max_skill_status; }
		else if (skill == "Enchanting") { enchanting_exp = skill_exp; enchanting_level = skill_level; max_enchanting_status = max_skill_status; }
		else if (skill == "Babric Weaving") { fabricWeaving_exp = skill_exp; fabricWeaving_level = skill_level; max_fabricWeaving_status = max_skill_status; }
		else if (skill == "Cooking") { cooking_exp = skill_exp; cooking_level = skill_level; max_cooking_status = max_skill_status; }
	}
}

/****************************************************************************************************/
void Character::gainItem(const char* item, bool print)
{
	if (inventory.size() >= max_inventory)
	{
		for (int j = 0; j < Log::getAllObjects().size(); j++) // just log object
			Log::getAllObjects()[j]->LogStore({std::string("Inventory is full.")});
	}
	else
	{
		inventory.push_back(item);
		if (print)
		{
			for (int j = 0; j < Log::getAllObjects().size(); j++) // just log object
			{
				item_str = std::string("Picked up ") + std::string(item) + std::string(".");
				Log::getAllObjects()[j]->LogStore({ item_str });
			}
		}
	}
}

/****************************************************************************************************/
void Character::gainGold(int gainedGold)
{
	gold += gainedGold;
	for (int j = 0; j < Log::getAllObjects().size(); j++) // just log object
	{
		gold_str = std::string("Gained ") + std::to_string(gainedGold) + std::string(" gold.");
		Log::getAllObjects()[j]->LogStore({ gold_str });
	}
}

/****************************************************************************************************/
void Character::healthRegen()
{	// Note: Stats are given the type double (decimals), but what is presented in stats bars is the nearest integer percentage.
	if (health < max_health)
	{
		health += 0.01 * max_health;
		health = std::min(health, max_health);
	}
	health_regen_switch = true;
}

/****************************************************************************************************/
void Character::staminaRegen()
{	// Note: Stats are given the type double (decimals), but what is presented in stats bars is the nearest integer percentage.
	if (stamina < max_stamina)
	{
		stamina += 0.05 * max_stamina;
		stamina = std::min(stamina, max_stamina);
	}
	stamina_regen_switch = true;
}

/****************************************************************************************************/
void Character::manaRegen()
{	// Note: Stats are given the type double (decimals), but what is presented in stats bars is the nearest integer percentage.
	if (mana < max_mana)
	{
		mana += 0.01 * max_mana;
		mana = std::min(mana, max_mana);
	}
	mana_regen_switch = true;
}
/****************************************************************************************************/
Uint32 Character::healthRegen_callback(Uint32 interval, void* param) // 1% max health every 10 seconds.
{
	// Note: Can either put function contents in here (must be static though) or can push an event to the queue where the nonstatic content function gets called when handling events.

	//for (int i = 0; i < getAllObjects().size(); i++) // just player object
	//{
	//	if (getAllObjects()[i]->health < getAllObjects()[i]->max_health)
	//	{
	//		getAllObjects()[i]->health += 0.01 * getAllObjects()[i]->max_health;
	//		getAllObjects()[i]->health = std::min(getAllObjects()[i]->health, getAllObjects()[i]->max_health);
	//	}
	//	getAllObjects()[i]->health_regen_switch = true;
	//}

	SDL_Event event;

	event.type = SDL_USEREVENT;
	event.user.code = HEALTH_REGEN;
	event.user.data1 = NULL;
	event.user.data2 = NULL;

	SDL_PushEvent(&event);

	return 0; // Only fire once every time this is called. Return interval if repeating.
}

/****************************************************************************************************/
Uint32 Character::staminaRegen_callback(Uint32 interval, void* param) // 5% max stamina every second
{
	SDL_Event event;

	event.type = SDL_USEREVENT;
	event.user.code = STAMINA_REGEN;
	event.user.data1 = NULL;
	event.user.data2 = NULL;

	SDL_PushEvent(&event);

	return 0; // Only fire once every time this is called. Return interval if repeating.
}

/****************************************************************************************************/
Uint32 Character::manaRegen_callback(Uint32 interval, void* param) // 1% max mana every 5 seconds
{
	SDL_Event event;

	event.type = SDL_USEREVENT;
	event.user.code = MANA_REGEN;
	event.user.data1 = NULL;
	event.user.data2 = NULL;

	SDL_PushEvent(&event);

	return 0; // Only fire once every time this is called. Return interval if repeating.
}