#include "Game.h"
#include "Draw.h"
#include "Character.h"
#include "Enemies.h"
#include "Item.h"
#include "Log.h"

std::vector<double> Enemy::distances; // List of distances between player and each enemy
std::vector<Enemy*> Enemy::objList; // List of enemy objects
std::vector<Character*> Character::objList; // List of character objects (just player)
std::vector<Map*> Map::objList; // List of map objects (just map)
std::vector<Log*> Log::objList; // List of log objects (just log)
std::vector<MapObject*>MapObject::objList; // List of MapObject objects

Character* player;
Enemy* bear1, *bunny1, *wolf1, *crab1, *boar1, *turtle1; // Eventually use a for loop to create multiple of each enemy. Have respawn system, death, loot dops, etc
Map* map;
MapObject* copper_ore, *iron_ore, *titanium_ore, *emerald_ore, *coal_ore, *gold_ore, *diamond_ore, *dragonscale_ore;
MapObject* red_yellow_flower;
//Item* test_item;
//CraftingItem* copper_bar;
Log* player_log; // "log" cannot be used because it thinks this is a function - logarithm probably.

SDL_Renderer* Game::renderer = nullptr;

Game::Game()
{}
Game::~Game()
{}

/****************************************************************************************************/
void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) // If calling SDL_Init function returns success (0)...
	{
		std::cout << "Subsystems Initialized!..." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "Window Created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer Created!" << std::endl;
		}

		if (TTF_Init() == 0)
		{
			std::cout << "TrueType Font SDL Extension Initialized!" << std::endl;

			title_font = TTF_OpenFont("assets/fonts/OpenSans-Bold.ttf", 32);
			enter_font = TTF_OpenFont("assets/fonts/OpenSans-Regular.ttf", 24);
			if ((title_font == NULL) | (enter_font == NULL))
			{
				std::cout << "Font failed to load!\n" << std::endl;
			}
			title_text = TextureManager::LoadText(title_font, title, { 0,0,0 });
			int title_width; int title_height; TTF_SizeText(title_font, title, &title_width, &title_height);
			title_rect.w = title_width; 
			title_rect.h = title_height; 
			title_rect.x = (Game::screenWidth / 2) - (title_rect.w / 2); 
			title_rect.y = (Game::screenHeight / 2) - (title_rect.h / 2) - 250; // Exactly centered but offset upwards

			enter_text = TextureManager::LoadText(enter_font, "Press Enter", { 0,0,0 });
			int enter_width; int enter_height; TTF_SizeText(enter_font, "Press Enter", &enter_width, &enter_height);
			enter_rect.w = enter_width;
			enter_rect.h = enter_height;
			enter_rect.x = (Game::screenWidth / 2) - (enter_rect.w / 2);
			enter_rect.y = (Game::screenHeight / 2) - (title_rect.h / 2) + 250; // Exactly centered but offset downward

			isRunning = true;
		}
	}
	else {
		isRunning = false;
	}

	player = new Character("assets/player_down_1.png", "assets/player_down_2.png", "assets/player_down_3.png", 
						   "assets/player_up_1.png", "assets/player_up_2.png", "assets/player_up_3.png",
						   "assets/player_left_1.png", "assets/player_left_2.png", "assets/player_left_3.png", 
						   "assets/player_right_1.png", "assets/player_right_2.png", "assets/player_right_3.png",
						   "assets/player_left_2_fishing.png", "assets/player_left_2_fishing_bubbles1.png", "assets/player_left_2_fishing_bubbles2.png",
						   "assets/player_left_2_fishing_catch1.png", "assets/player_left_2_fishing_catch2.png",
						   "assets/player_right_2_fishing.png", "assets/player_right_2_fishing_bubbles1.png", "assets/player_right_2_fishing_bubbles2.png",
						   "assets/player_right_2_fishing_catch1.png", "assets/player_right_2_fishing_catch2.png",
						   21, 24, 21, 21, 24, 21, 15, 11, 15, 15, 11, 15, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 
						   51, 51, 33, 33, 4);

	bear1 = new Enemy("assets/bear_1.png", "assets/bear_2.png", "assets/bear_3.png",
					  "assets/bear_10.png", "assets/bear_11.png", "assets/bear_12.png",
		              "assets/bear_4.png", "assets/bear_5.png", "assets/bear_6.png",
		              "assets/bear_7.png", "assets/bear_8.png", "assets/bear_9.png", 
		              53, 52, 53, 50, 49, 50, 80, 80, 80, 80, 80, 80, // w_down, up, left, right
				      80, 80, 80, 80, 80, 80, 53, 55, 53, 53, 55, 53, // h_down, up, left, right
		              220, 220, 200, 200, 1000, 600, 2, 100, 1);		  // x, y, containment_left, top, w, h, dest_rect_multiple, health_max, threat
	bunny1 = new Enemy("assets/bunny_1.png", "assets/bunny_2.png", "assets/bunny_3.png",
					   "assets/bunny_10.png", "assets/bunny_11.png", "assets/bunny_12.png",
					   "assets/bunny_4.png", "assets/bunny_5.png", "assets/bunny_6.png",
					   "assets/bunny_7.png", "assets/bunny_8.png", "assets/bunny_9.png", 
					   19, 19, 19, 19, 19, 19, 29, 28, 29, 29, 28, 29,
					   23, 24, 25, 32, 31, 32, 24, 24, 24, 24, 24, 24,
					   220, 220, 200, 200, 1000, 600, 2, 5, 0);
	wolf1 = new Enemy("assets/wolf_1.png", "assets/wolf_2.png", "assets/wolf_3.png",
					  "assets/wolf_10.png", "assets/wolf_11.png", "assets/wolf_12.png",
					  "assets/wolf_4.png", "assets/wolf_5.png", "assets/wolf_6.png",
					  "assets/wolf_7.png", "assets/wolf_8.png", "assets/wolf_9.png",
					  34, 34, 34, 31, 30, 31, 64, 64, 64, 64, 64, 64,
					  64, 64, 64, 64, 64, 64, 42, 41, 42, 42, 41, 42,
					  220, 220, 200, 200, 1000, 600, 2, 75, 1);
	crab1 = new Enemy("assets/crab_1.png", "assets/crab_2.png", "assets/crab_3.png",
					  "assets/crab_10.png", "assets/crab_11.png", "assets/crab_12.png",
					  "assets/crab_4.png", "assets/crab_5.png", "assets/crab_6.png",
					  "assets/crab_7.png", "assets/crab_8.png", "assets/crab_9.png", 
					  41, 41, 41, 41, 41, 41, 33, 32, 36, 33, 32, 36,
					  31, 29, 31, 20, 20, 20, 27, 27, 27, 27, 27, 27,
					  220, 220, 200, 200, 1000, 600, 2, 50, 2);
	boar1 = new Enemy("assets/boar_1.png", "assets/boar_2.png", "assets/boar_3.png",
					  "assets/boar_10.png", "assets/boar_11.png", "assets/boar_12.png",
					  "assets/boar_4.png", "assets/boar_5.png", "assets/boar_6.png",
					  "assets/boar_7.png", "assets/boar_8.png", "assets/boar_9.png", 
					  37, 37, 37, 32, 31, 31, 60, 60, 60, 60, 60, 60,
					  60, 60, 60, 60, 60, 60, 40, 41, 40, 40, 41, 40,
					  220, 220, 200, 200, 1000, 600, 2, 50, 1);
	turtle1 = new Enemy("assets/turtle_1.png", "assets/turtle_2.png", "assets/turtle_3.png",
					    "assets/turtle_10.png", "assets/turtle_11.png", "assets/turtle_12.png",
						"assets/turtle_4.png", "assets/turtle_5.png", "assets/turtle_6.png",
					    "assets/turtle_7.png", "assets/turtle_8.png", "assets/turtle_9.png", 
						41, 41, 41, 36, 36, 36, 50, 50, 50, 50, 50, 50,
						50, 50, 50, 50, 50, 50, 32, 32, 32, 32, 32, 32,
						220, 220, 200, 200, 1000, 600, 2, 50, 2);
	map = new Map();

	copper_ore = new MapObject("assets/ore_copper.png", 1300, 500, 23, 21, 3); // asset, x, y, w, h, dest_rect_mult
	iron_ore = new MapObject("assets/ore_iron.png", 1500, 500, 23, 21, 3);
	titanium_ore = new MapObject("assets/ore_titanium.png", 1700, 500, 23, 21, 3);
	emerald_ore = new MapObject("assets/ore_emerald.png", 1900, 500, 23, 21, 3);
	coal_ore = new MapObject("assets/ore_coal.png", 2100, 500, 23, 21, 3);
	gold_ore = new MapObject("assets/ore_gold.png", 2300, 500, 23, 21, 3);
	diamond_ore = new MapObject("assets/ore_diamond.png", 2500, 500, 23, 21, 3);
	dragonscale_ore = new MapObject("assets/ore_dragonscale.png", 2700, 500, 23, 21, 3);

	red_yellow_flower = new MapObject("assets/red_yellow_flower.png", 1300, 800, 29, 19, 2);

	//test_item = new Item("assets/ore_copper.png", "Test Item", "Test Description", 1, 1);
	//copper_bar = new CraftingItem({ "Armoring", "Blacksmithing" }, 1, 20, "assets/ore_copper.png", "Copper Bar", "A bar of solid copper.", 14, 1);

	player_log = new Log("assets/logSurface.png");
}

/****************************************************************************************************/
void Game::class_render()
{
	class_font = TTF_OpenFont("assets/fonts/OpenSans-Regular.ttf", 24);
	if (class_font == NULL)
	{
		std::cout << "Font failed to load!\n" << std::endl;
	}

	int sep = 200;

	class_text = TextureManager::LoadText(class_font, "Choose a Class:", { 0,0,0 });
	int class_width; int class_height; TTF_SizeText(class_font, "Choose a Class:", &class_width, &class_height);
	class_rect.w = class_width;
	class_rect.h = class_height;
	class_rect.x = (Game::screenWidth / 6) - (class_rect.w / 2);
	class_rect.y = (Game::screenHeight / 8) - (class_rect.h / 2);

	warrior_text = TextureManager::LoadText(class_font, "1.)   Warrior", { 0,0,0 });
	int warrior_width; int warrior_height; TTF_SizeText(class_font, "1.)   Warrior", &warrior_width, &warrior_height);
	warrior_rect.w = warrior_width;
	warrior_rect.h = warrior_height;
	warrior_rect.x = (Game::screenWidth / 6);
	warrior_rect.y = (Game::screenHeight / 8) + 100;

	warrior_text2 = TextureManager::LoadText(class_font, "Tank specialist and melee combat.", { 0,0,0 });
	int warrior_width2; int warrior_height2; TTF_SizeText(class_font, "Tank specialist and melee combat.", &warrior_width2, &warrior_height2);
	warrior_rect2.w = warrior_width2;
	warrior_rect2.h = warrior_height2;
	warrior_rect2.x = (Game::screenWidth / 6) + sep;
	warrior_rect2.y = (Game::screenHeight / 8) + 100;

	rogue_text = TextureManager::LoadText(class_font, "2.)   Rogue", { 0,0,0 });
	int rogue_width; int rogue_height; TTF_SizeText(class_font, "2.)   Rogue", &rogue_width, &rogue_height);
	rogue_rect.w = rogue_width;
	rogue_rect.h = rogue_height;
	rogue_rect.x = (Game::screenWidth / 6);
	rogue_rect.y = (Game::screenHeight / 8) + 220;

	rogue_text2 = TextureManager::LoadText(class_font, "Stealth specialist and melee combat.", { 0,0,0 });
	int rogue_width2; int rogue_height2; TTF_SizeText(class_font, "Stealth specialist and melee combat.", &rogue_width2, &rogue_height2);
	rogue_rect2.w = rogue_width2;
	rogue_rect2.h = rogue_height2;
	rogue_rect2.x = (Game::screenWidth / 6) + sep;
	rogue_rect2.y = (Game::screenHeight / 8) + 220;

	predator_text = TextureManager::LoadText(class_font, "3.)   Predator", { 0,0,0 });
	int predator_width; int predator_height; TTF_SizeText(class_font, "3.)   Predator", &predator_width, &predator_height);
	predator_rect.w = predator_width;
	predator_rect.h = predator_height;
	predator_rect.x = (Game::screenWidth / 6);
	predator_rect.y = (Game::screenHeight / 8) + 340;

	predator_text2 = TextureManager::LoadText(class_font, "Ranged bow specialist. Can tame beasts.", { 0,0,0 });
	int predator_width2; int predator_height2; TTF_SizeText(class_font, "Ranged bow specialist. Can tame beasts.", &predator_width2, &predator_height2);
	predator_rect2.w = predator_width2;
	predator_rect2.h = predator_height2;
	predator_rect2.x = (Game::screenWidth / 6) + sep;
	predator_rect2.y = (Game::screenHeight / 8) + 340;

	mystic_text = TextureManager::LoadText(class_font, "4.)   Mystic", { 0,0,0 });
	int mystic_width; int mystic_height; TTF_SizeText(class_font, "4.)   Mystic", &mystic_width, &mystic_height);
	mystic_rect.w = mystic_width;
	mystic_rect.h = mystic_height;
	mystic_rect.x = (Game::screenWidth / 6);
	mystic_rect.y = (Game::screenHeight / 8) + 460;

	mystic_text2 = TextureManager::LoadText(class_font, "Elemental magic damage specialist. Casts spells dealing instant damage.", { 0,0,0 });
	int mystic_width2; int mystic_height2; TTF_SizeText(class_font, "Elemental magic damage specialist. Casts spells dealing instant damage.", &mystic_width2, &mystic_height2);
	mystic_rect2.w = mystic_width2;
	mystic_rect2.h = mystic_height2;
	mystic_rect2.x = (Game::screenWidth / 6) + sep;
	mystic_rect2.y = (Game::screenHeight / 8) + 460;

	cultist_text = TextureManager::LoadText(class_font, "5.)   Cultist", { 0,0,0 });
	int cultist_width; int cultist_height; TTF_SizeText(class_font, "5.)   Cultist", &cultist_width, &cultist_height);
	cultist_rect.w = cultist_width;
	cultist_rect.h = cultist_height;
	cultist_rect.x = (Game::screenWidth / 6);
	cultist_rect.y = (Game::screenHeight / 8) + 580;

	cultist_text2 = TextureManager::LoadText(class_font, "Dark magic damage specialist. Casts damage over time spells.", { 0,0,0 });
	int cultist_width2; int cultist_height2; TTF_SizeText(class_font, "Dark magic damage specialist. Casts damage over time spells.", &cultist_width2, &cultist_height2);
	cultist_rect2.w = cultist_width2;
	cultist_rect2.h = cultist_height2;
	cultist_rect2.x = (Game::screenWidth / 6) + sep;
	cultist_rect2.y = (Game::screenHeight / 8) + 580;

	priest_text = TextureManager::LoadText(class_font, "6.)   Priest", { 0,0,0 });
	int priest_width; int priest_height; TTF_SizeText(class_font, "6.)   Priest", &priest_width, &priest_height);
	priest_rect.w = priest_width;
	priest_rect.h = priest_height;
	priest_rect.x = (Game::screenWidth / 6);
	priest_rect.y = (Game::screenHeight / 8) + 700;

	priest_text2 = TextureManager::LoadText(class_font, "Divine magic damage and healing specialist.", { 0,0,0 });
	int priest_width2; int priest_height2; TTF_SizeText(class_font, "Divine magic damage and healing specialist.", &priest_width2, &priest_height2);
	priest_rect2.w = priest_width2;
	priest_rect2.h = priest_height2;
	priest_rect2.x = (Game::screenWidth / 6) + sep;
	priest_rect2.y = (Game::screenHeight / 8) + 700;
}

/****************************************************************************************************/
void Game::class_init(int index)
{
	if ((index < 1) | (index > 6))
	{
		std::cout << "Error: Choose a class 1-6." << std::endl;
	}
	else
	{
		player->abilities.push_back("Teleport");
		player->abilities.push_back("Base Attack");

		if (index == 1)
		{
			player->Warrior = true;
			player->max_health = 100;
			player->max_stamina = 30;
			player->max_mana = -1;
			player->base_dmg = 10;
			player->dodge_chance = 0.02;
			player->armour = 50;
			player->max_range = 150;
			player->base_heal = -1;
			player->abilities.push_back("Harden");
			player->stamina_regen_switch = true;
		}
		else if (index == 2)
		{
			player->Rogue = true;
			player->max_health = 80;
			player->max_stamina = 50;
			player->max_mana = -1;
			player->base_dmg = 14;
			player->dodge_chance = 0.05;
			player->armour = 30;
			player->max_range = 150;
			player->base_heal = -1;
			player->abilities.push_back("Puncture");
			player->stamina_regen_switch = true;
		}
		else if (index == 3)
		{
			player->Predator = true;
			player->max_health = 85;
			player->max_stamina = 40;
			player->max_mana = -1;
			player->base_dmg = 12;
			player->dodge_chance = 0.02;
			player->armour = 30;
			player->max_range = 250;
			player->base_heal = -1;
			player->abilities.push_back("Kick");
			player->stamina_regen_switch = true;
		}
		else if (index == 4)
		{
			player->Mystic = true;
			player->max_health = 70;
			player->max_stamina = -1;
			player->max_mana = 90;
			player->base_dmg = 12;
			player->dodge_chance = 0.02;
			player->armour = 10;
			player->max_range = 300;
			player->base_heal = 5;
			player->abilities.push_back("Elemental Call");
			player->mana_regen_switch = true;
		}
		else if (index == 5)
		{
			player->Cultist = true;
			player->max_health = 70;
			player->max_stamina = -1;
			player->max_mana = 90;
			player->base_dmg = 8;
			player->dodge_chance = 0.02;
			player->armour = 10;
			player->max_range = 300;
			player->base_heal = 5;
			player->abilities.push_back("Curse");
			player->mana_regen_switch = true;
		}
		else if (index == 6)
		{
			player->Priest = true;
			player->max_health = 65;
			player->max_stamina = -1;
			player->max_mana = 100;
			player->base_dmg = 8;
			player->dodge_chance = 0.02;
			player->armour = 10;
			player->max_range = 300;
			player->base_heal = 15;
			player->abilities.push_back("Flash of Light");
			player->mana_regen_switch = true;
		}

		player->health = player->max_health;
		player->stamina = player->max_stamina;
		player->mana = player->max_mana;
	}
}

/****************************************************************************************************/
void Game::handleEvents()
{
	//single-press keys and mouse
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	case SDL_USEREVENT:
		switch (event.user.code)
		{
		case Character::HEALTH_REGEN:
			player->healthRegen();
			break;
		case Character::STAMINA_REGEN:
			player->staminaRegen();
			break;
		case Character::MANA_REGEN:
			player->manaRegen();
			break;
		case Character::BASE_ATTACK:
		{
			int enemy_int = 0;
			for (Enemy* obj : Enemy::getAllObjects())
			{
				if (obj == static_cast<Enemy*>(event.user.data1))
					break;
				enemy_int++;
			}
			player->Attack(enemy_int);
			break;
		}
		case Character::BASE_ATTACK_COOLDOWN:
			player->initAttackCoolDown();
			break;
		case Enemy::BASE_ATTACK:
			static_cast<Enemy*>(event.user.data1)->attack();
			break;
		case Enemy::BASE_ATTACK_COOLDOWN:
			static_cast<Enemy*>(event.user.data1)->initAttackCoolDown();
			break;
		default:
			break;
		}
		break;
	
	case SDL_KEYDOWN:
		if (event.key.repeat == 0)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				isRunning = false; // Pull up pause menu instead, eventually.
			}
			if (event.key.keysym.sym == SDLK_l) // Open log book
			{
				if (!player_log->logLoop)
					player_log->logLoop = true;
				else
					player_log->logLoop = false;
			}
			if (event.key.keysym.sym == SDLK_c) // Clear log book
			{
				if (player_log->logLoop)
					player_log->LogClear();
			}
			if (event.key.keysym.sym == SDLK_g) // Get gold
			{
				player->gainGold(10);
			}
			if (event.key.keysym.sym == SDLK_i) // Pick up item
			{
				player->gainItem("Iron Short Sword", true);
			}
			if (event.key.keysym.sym == SDLK_e) // Get exp
			{
				player->gainExp(40);
			}
			if (event.key.keysym.sym == SDLK_k) // Get fishing exp
			{
				player->gainSkillExp(20, "Fishing");
			}
			if (event.key.keysym.sym == SDLK_f) // Start fishing
			{
				if (std::find(player->inventory.begin(), player->inventory.end(), "Old Fishing Rod") != player->inventory.end())
				{
					// TODO: If the stuff below is true (outside of this f press condition), then have something say "Press f to start fishing".
					if ((player->stand) and (player->inaccessible_area) and (player->inaccessible_tile_type == 2))
					{
						if (player->inventory.size() < player->max_inventory)
							player->isFishing = true;
						else
							player_log->LogStore({ std::string("Inventory is full.") });
					}
				}
				else
					player_log->LogStore({ std::string("No fishing rod in inventory.") });
			}
			if (event.key.keysym.sym == SDLK_RETURN)
			{
				if (player->isFishing)
				{
					if (player->fish_bite)
					{
						// Add catch to inventory based on probability, increase fishing exp depending on the catch, and interrupt fishing.
						player->catchFish();
						player->interruptFishing();
					}
					else
					{
						// Failed fishing attempt. Interrupt fishing.
						player->interruptFishing();
					}
				}
			}
			if (event.key.keysym.sym == SDLK_TAB) // Highlight the closest enemy
			{
				for (int i = 0; i < Enemy::getAllObjects().size(); i++)
				{
					if (Enemy::getAllObjects()[i]->tabReady)
					{
						if (Enemy::getAllObjects()[i]->attackLoop)
						{
							Enemy::ClearHighlights();
							Enemy::getAllObjects()[i]->attack_highlighted = true;
						}
						else
						{
							Enemy::ClearHighlights();
							Enemy::getAllObjects()[i]->highlighted = true;
						}
					}
				}
			}
		}
		break;

	case SDL_MOUSEWHEEL:
		SDL_GetMouseState(&mouse_x, &mouse_y);
		if (event.wheel.y > 0) // Scroll up
		{
			if ((player_log->logLoop) & (mouse_x <= player_log->logSurface_rect.x + player_log->logSurface_rect.w) & (mouse_x >= player_log->logSurface_rect.x) & (mouse_y <= player_log->logSurface_rect.y + player_log->logSurface_rect.h) & (mouse_y >= player_log->logSurface_rect.y))
				player_log->LogScroll(true);
		}
		else if (event.wheel.y < 0) // Scroll down
		{
			if ((player_log->logLoop) & (mouse_x <= player_log->logSurface_rect.x + player_log->logSurface_rect.w) & (mouse_x >= player_log->logSurface_rect.x) & (mouse_y <= player_log->logSurface_rect.y + player_log->logSurface_rect.h) & (mouse_y >= player_log->logSurface_rect.y))
				player_log->LogScroll(false);
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		SDL_GetMouseState(&mouse_x, &mouse_y);
		
		switch (event.button.button)
		{
		case SDL_BUTTON_LEFT:
			highlight_count = 0;
			for (int i = 0; i < Enemy::getAllObjects().size(); i++)
			{
				if ((mouse_x >= Enemy::getAllObjects()[i]->current_destRect.x) & (mouse_x < Enemy::getAllObjects()[i]->current_destRect.x + Enemy::getAllObjects()[i]->current_destRect.w) & (mouse_y >= Enemy::getAllObjects()[i]->current_destRect.y) & (mouse_y < Enemy::getAllObjects()[i]->current_destRect.y + Enemy::getAllObjects()[i]->current_destRect.h))
				{
					Enemy::ClearHighlights();
					Enemy::getAllObjects()[i]->highlighted = true;
					highlight_count++;
				}
			}
			if (highlight_count == 0)
				Enemy::ClearHighlights();
			break;
		case SDL_BUTTON_RIGHT:
			highlight_count = 0;
			for (int i = 0; i < Enemy::getAllObjects().size(); i++)
			{
				if ((mouse_x >= Enemy::getAllObjects()[i]->current_destRect.x) & (mouse_x < Enemy::getAllObjects()[i]->current_destRect.x + Enemy::getAllObjects()[i]->current_destRect.w) & (mouse_y >= Enemy::getAllObjects()[i]->current_destRect.y) & (mouse_y < Enemy::getAllObjects()[i]->current_destRect.y + Enemy::getAllObjects()[i]->current_destRect.h))
				{
					Enemy::ClearHighlights();
					Enemy::getAllObjects()[i]->attack_highlighted = true;
					highlight_count++;
				}
			}
			if (highlight_count == 0)
				Enemy::ClearHighlights();
			break;
		}
		break;
	}

	keystate = SDL_GetKeyboardState(NULL);
	//continuous-response keys

	//up
	if ((keystate[SDL_SCANCODE_W]) & (player->ypos > map->map_y))
	{
		player->up = true;
		player->down = false;
		player->left = false;
		player->right = false;
		player->stand = false;
	}
	//down
	else if ((keystate[SDL_SCANCODE_S]) & ((player->ypos + player->destRect_down_1.h < map->map_y + (Map::num_chunks_h * Game::screenHeight)) & (player->ypos + player->destRect_down_2.h < map->map_y + (Map::num_chunks_h * Game::screenHeight)) & (player->ypos + player->destRect_down_3.h < map->map_y + (Map::num_chunks_h * Game::screenHeight))))
	{
		player->up = false;
		player->down = true;
		player->left = false;
		player->right = false;
		player->stand = false;
	}
	//left
	else if ((keystate[SDL_SCANCODE_A]) & (player->xpos > map->map_x))
	{
		player->up = false;
		player->down = false;
		player->left = true;
		player->right = false;
		player->stand = false;
	}
	//right
	else if ((keystate[SDL_SCANCODE_D]) & ((player->xpos + player->destRect_right_1.w < map->map_x + (Map::num_chunks_w * Game::screenWidth)) & (player->xpos + player->destRect_right_2.w < map->map_x + (Map::num_chunks_w * Game::screenWidth)) & (player->xpos + player->destRect_right_3.w < map->map_x + (Map::num_chunks_w * Game::screenWidth))))
	{
		player->up = false;
		player->down = false;
		player->left = false;
		player->right = true;
		player->stand = false;
	}
	// standing still
	else
	{
		player->stand = true;
	}
}

/****************************************************************************************************/
void Game::update()
{
	Enemy::AllDistancesToPlayer(); // contained in vector called distances

	// Do stuff with distances here...

	// Print distances
	/*
	for (auto i = distances.begin(); i != distances.end(); ++i)
		std::cout << *i << ",";
	std::cout << " " << std::endl;
	*/

	for (int i = 0; i < Enemy::getAllObjects().size(); i++)
	{	
		Enemy::getAllObjects()[i]->xDistanceToPlayer();
		Enemy::getAllObjects()[i]->yDistanceToPlayer();

		Enemy::getAllObjects()[i]->tabReady = false;
		if (Enemy::distances[i] <= player->tab_range)
		{
			//Enemy::getAllObjects()[i]->inRange = true;
			if (Enemy::distances[i] == *std::min_element(Enemy::distances.begin(), Enemy::distances.end()))
			{
				Enemy::getAllObjects()[i]->tabReady = true;
			}
		}
		/*
		else
		{
			Enemy::getAllObjects()[i]->inRange = false;
		}
		*/
		if ((Enemy::distances[i] <= Enemy::aggro_dist) & (Enemy::getAllObjects()[i]->threat == 1) & (!Enemy::getAllObjects()[i]->attackLoop))
		{
			Enemy::getAllObjects()[i]->attackLoop = true;
			if (!Enemy::AnyHighlighted(true, false))
			{
				Enemy::ClearHighlights();
				Enemy::getAllObjects()[i]->attack_highlighted = true;
			}
		}
	}
	
	player->Update();
	Enemy::UpdateAll();

	Enemy::distances.clear(); // resets distances vector

	// Eventually update map here by loading external file (text file with 0's, 1's, 2's etc.)
}

/****************************************************************************************************/
void Game::render()
{
	SDL_RenderClear(renderer);

	// Add stuff to render
	map->DrawNeighborChunks();
	MapObject::DrawAllObjects();
	Enemy::RenderAll();
	player->Render();

	if (player_log->logLoop)
	{
		player_log->LogRenderSurface();
		player_log->LogRenderText();
	}

	SDL_RenderPresent(renderer);
}

/****************************************************************************************************/
void Game::clean()
{
	TTF_CloseFont(class_font);
	TTF_CloseFont(player->stats_font);
	TTF_CloseFont(player_log->log_font);
	TTF_Quit();

	SDL_RemoveTimer(player->health_regen_timer);
	SDL_RemoveTimer(player->stamina_regen_timer);
	SDL_RemoveTimer(player->mana_regen_timer);

	map->ClearDrawVectors();

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}

/****************************************************************************************************/
bool Game::running()
{
	return isRunning;
}

/****************************************************************************************************/
double Game::getRandom()
{
	static std::default_random_engine e;
	static std::uniform_real_distribution<> dis(0, 1); // range 0 - 1
	return dis(e);
}
