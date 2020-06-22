#ifndef CHARACTER_H
#define CHARACTER_H

#include "Game.h"
#include "Enemies.h"

struct SkillItem {
	// chance is the sucessful acquisition of the skill item for each lvl bracket (1-5, 6-10, ..., 46-50)
	// stats are different for each skill: 
	// Fish --> exp_gained, raw_hps, cooked_hps, raw_worth, cooked_worth, rarity
	// Ore/Bars --> exp_gained, worth, min_skill_lvl, rarity
	// min_item is the minimum item needed to acquire the skill item
	// hps = health per second over 5 seconds | rarity --> 0 - Rubbish, 1 - Very Common, 2 - Common, 3 - Rare, 4 - Very Rare, 5 - Exceptional, 6 - Fabled
	static const int num_lvl_brackets = 10;
	std::vector<int> chance;
	std::vector<int> stats;
	const char* name;
	std::vector<std::string> min_items;
	const char* description;
};

class Character {

public:
	Character(const char* tex_down_1, const char* tex_down_default, const char* tex_down_3,
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
			  int dest_rect_multiple);
	~Character();

	static std::vector<Character*> getAllObjects();

	void Update();
	void Render();
	SDL_Rect Animate(SDL_Texture* tex, SDL_Texture* tex_default, SDL_Texture* tex_3);
	void Fishing_Animate(SDL_Texture* tex_1, SDL_Texture* tex_default, SDL_Texture* tex_2);
	void Fish_Bite_Animate(SDL_Texture* tex_1, SDL_Texture* tex_2);
	void Fishing();
	void catchFish();
	void interruptFishing();
	void baseAttack(int enemy_int);
	void Attack(int enemy_int);
	void initAttackCoolDown();
	void DrawHitbox(int r, int g, int b, int a);
	void DrawHealthBar();
	void DrawStaminaBar();
	void DrawManaBar();
	void gainExp(int gainedExp);
	void gainSkillExp(int gainedSkillExp, const char* skill);
	void gainItem(const char* item, bool print);
	void gainGold(int gainedGold);
	void healthRegen();
	void staminaRegen();
	void manaRegen();
	static Uint32 healthRegen_callback(Uint32 interval, void* param); // Callback functions as member functions of a class must be declared static
	static Uint32 staminaRegen_callback(Uint32 interval, void* param);
	static Uint32 manaRegen_callback(Uint32 interval, void* param);
	static Uint32 attack_callback(Uint32 interval, void* param);
	static Uint32 initAttackCoolDown_callback(Uint32 interval, void* param);

	bool inaccessible_area;
	int inaccessible_tile_type;

	static const int HEALTH_REGEN = 1;
	static const int STAMINA_REGEN = 2;
	static const int MANA_REGEN = 3;
	static const int BASE_ATTACK = 4;
	static const int BASE_ATTACK_COOLDOWN = 5;

	SDL_TimerID health_regen_timer;
	SDL_TimerID stamina_regen_timer;
	SDL_TimerID mana_regen_timer;
	SDL_TimerID attack_timer;
	SDL_TimerID initAttackCoolDown_timer;

	double health_regen;
	double stamina_regen;
	double mana_regen;

	int xpos;
	int ypos;
	int max_vel = 8;

	bool up;
	bool down;
	bool left;
	bool right;
	bool stand;

	bool Warrior; bool Rogue; bool Predator; bool Mystic; bool Cultist; bool Priest;

	double health;
	double max_health;
	double stamina;
	double max_stamina;
	double mana;
	double max_mana;

	bool health_regen_switch;
	bool stamina_regen_switch;
	bool mana_regen_switch;
	
	double base_dmg;
	double crit_chance;
	double crit_dmg_mult;
	double dodge_chance;
	double armour;
	double max_range;
	double tab_range = 600;
	double base_heal;

	bool base_attack_loop;
	bool initialAttack;
	bool initSwitch;

	std::vector<const char*> abilities;
	std::vector<const char*> tele_home;
	std::vector<const char*> inventory;

	std::vector<SkillItem> fish;
	std::vector<std::vector<int>> fish_data;
	bool isFishing;
	bool fish_bite;
	int fishing_frame = 0;
	int fishing_frames_tot = 48;
	int fish_bite_frame = 0;
	int fish_bite_frames_tot = 12;
	int fishingLoopCount = 0;
	int fishingLoopCount_Reset = 40; // 140
	int fishingLoopTotal = 0;
	float catch_chance;
	float fish_prob;

	std::vector<SkillItem> ores;
	std::vector<std::vector<int>> ore_data;

	std::vector<SkillItem> bars;
	std::vector<std::vector<int>> bar_data;

	int gold;
	int max_inventory;
	int exp;
	int expThreshold[50];
	int skillExpThreshold[50];
	int level;
	int max_level;
	bool max_level_status;
	int max_skill_level;

	int blacksmithing_level;
	int armoring_level;
	int smelting_level;
	int mining_level;
	//int gardening_level;
	int herbGathering_level;
	int alchemy_level;
	int fishing_level;
	int enchanting_level;
	int fabricWeaving_level;
	int cooking_level;

	int blacksmithing_exp;
	int armoring_exp;
	int smelting_exp;
	int mining_exp;
	//int gardening_exp;
	int herbGathering_exp;
	int alchemy_exp;
	int fishing_exp;
	int enchanting_exp;
	int fabricWeaving_exp;
	int cooking_exp;

	bool max_blacksmithing_status;
	bool max_armoring_status;
	bool max_smelting_status;
	bool max_mining_status;
	//bool max_gardening_status;
	bool max_herbGathering_status;
	bool max_alchemy_status;
	bool max_fishing_status;
	bool max_enchanting_status;
	bool max_fabricWeaving_status;
	bool max_cooking_status;

	static const int bar_width = 200;
	static const int bar_height = 20;
	SDL_Rect health_rect_behind; SDL_Rect stamina_rect_behind; SDL_Rect mana_rect_behind;
	SDL_Rect health_rect_front; SDL_Rect stamina_rect_front; SDL_Rect mana_rect_front;
	TTF_Font* stats_font;
	SDL_Texture* health_text; SDL_Texture* stamina_text; SDL_Texture* mana_text;
	std::string health_str; std::string stamina_str; std::string mana_str;
	const char* health_char; const char* stamina_char; const char* mana_char;
	SDL_Rect health_rect; SDL_Rect stamina_rect; SDL_Rect mana_rect;

	SDL_Rect destRect_down_1, destRect_down_2, destRect_down_3, destRect_up_1, destRect_up_2, destRect_up_3;
	SDL_Rect destRect_left_1, destRect_left_2, destRect_left_3, destRect_right_1, destRect_right_2, destRect_right_3;
	SDL_Rect destRect_left_2_fishing, destRect_right_2_fishing;

	SDL_Rect current_destRect = destRect_down_2;

	std::string item_str;
	std::string gold_str;
	std::string skilllevel_str;
	std::string skillmaxlevel_str;
	std::string skillexp_str;
	std::string level_str;
	std::string maxlevel_str;
	std::string exp_str;
	std::string catch_str;

private:
	static std::vector<Character*> objList; // list of all objects of this class

	int frame = 0;
	int walking_frames = 12; // The number of frames before the updated animation renders.

	SDL_Texture* charTexture_Up_1, * charTexture_Up_Default, * charTexture_Up_3;
	SDL_Texture* charTexture_Down_1, * charTexture_Down_Default, * charTexture_Down_3;
	SDL_Texture* charTexture_Left_1, * charTexture_Left_Default, * charTexture_Left_3;
	SDL_Texture* charTexture_Right_1, * charTexture_Right_Default, * charTexture_Right_3;
	SDL_Texture* charTexture_Left_2_Fishing, * charTexture_Left_2_Fishing_Bubbles1, * charTexture_Left_2_Fishing_Bubbles2;
	SDL_Texture* charTexture_Left_2_Fishing_Catch1, * charTexture_Left_2_Fishing_Catch2;
	SDL_Texture* charTexture_Right_2_Fishing, * charTexture_Right_2_Fishing_Bubbles1, * charTexture_Right_2_Fishing_Bubbles2;
	SDL_Texture* charTexture_Right_2_Fishing_Catch1, * charTexture_Right_2_Fishing_Catch2;
	
	SDL_Rect srcRect_down_1, srcRect_down_2, srcRect_down_3, srcRect_up_1, srcRect_up_2, srcRect_up_3;
	SDL_Rect srcRect_left_1, srcRect_left_2, srcRect_left_3, srcRect_right_1, srcRect_right_2, srcRect_right_3;
	SDL_Rect srcRect_left_2_fishing, srcRect_right_2_fishing;
};

#endif /* CHARACTER_H */