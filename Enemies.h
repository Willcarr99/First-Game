#ifndef ENEMIES_H
#define ENEMIES_H

#include "Game.h"

class Enemy {

public:
	Enemy(const char* tex_down_1, const char* tex_down_default, const char* tex_down_3,
		const char* tex_up_1, const char* tex_up_default, const char* tex_up_3,
		const char* tex_left_1, const char* tex_left_default, const char* tex_left_3,
		const char* tex_right_1, const char* tex_right_default, const char* tex_right_3,
		int w_down_1, int w_down_2, int w_down_3, int w_up_1, int w_up_2, int w_up_3,
		int w_left_1, int w_left_2, int w_left_3, int w_right_1, int w_right_2, int w_right_3,
		int h_down_1, int h_down_2, int h_down_3, int h_up_1, int h_up_2, int h_up_3,
		int h_left_1, int h_left_2, int h_left_3, int h_right_1, int h_right_2, int h_right_3,
		int x, int y, int containment_left, int containment_top, int containment_w, int containment_h, 
		int dest_rect_multiple, double health_max, int threat_level);
	~Enemy();

	static std::vector<Enemy*> getAllObjects();
	static void MoveObjectsDown(int max_vel);
	static void MoveObjectsUp(int max_vel);
	static void MoveObjectsLeft(int max_vel);
	static void MoveObjectsRight(int max_vel);
	static std::vector<double> distances;

	static void UpdateAll();
	static void RenderAll();
	static void AllDistancesToPlayer();
	static void ClearHighlights();
	static bool AnyHighlighted(bool attack_highlight, bool highlight);
	static int AttackHighlightedEnemy();

	void Update();
	void Render();
	SDL_Rect Animate(SDL_Texture* tex, SDL_Texture* tex_default, SDL_Texture* tex_3);
	void Movement();
	bool Chase(bool prev_path);
	void attack();
	void initAttackCoolDown();
	void xDistanceToPlayer();
	void yDistanceToPlayer();
	double DistanceToPlayer();
	double DistCalc(int player_x, int player_y, int player_w, int player_h, int enemy_x, int enemy_y, int enemy_w, int enemy_h);
	void DrawHitbox(int r, int g, int b, int a);
	void DrawHealthBar();
	void DrawContainmentBox(int r, int g, int b, int a);
	static Uint32 attack_callback(Uint32 interval, void* param);
	static Uint32 initAttackCoolDown_callback(Uint32 interval, void* param);

	static const int BASE_ATTACK = 6;
	static const int BASE_ATTACK_COOLDOWN = 7;

	SDL_TimerID attack_timer;
	SDL_TimerID initAttackCoolDown_timer;

	int xpos;
	int ypos;
	double dx;
	double dy;
	double dist;
	bool inRange = false;
	bool tabReady = false;

	int threat; // 0 - will not attack. 1 - will attack if within aggro dist. 2 - will not aggro, but will attack back.
	static const int aggro_dist = 300;
	bool horizontal_path;
	bool attackLoop = false;
	bool damageLoop = false;
	bool initialAttack = true;
	bool initialSwitch = true;
	bool highlighted = false;
	bool attack_highlighted = false;
	
	// Need to multiply these by about 2 because the player and enemy sizes are about twice as big in this game
	const int chase_buffer = 24*2; // 24
	const int path_offset1 = 6*2; // 6
	const int path_offset2 = 24*2; // 24
	const int path_offset3 = 0*2; // 0
	const int path_offset4 = 0*2; // 6 (changed chase player down from offset1 to offset4)
	const int path_offset5 = 24*2; // 24 ( changed chase player below -> horizontal from offset2 to offset5)

	double health;
	double max_health;
	int level = 3;
	int exp_given = pow(level, 2);
	double base_dmg = double(5 * level);
	double dodge_chance = 0.03;
	double crit_chance = 0.05;
	double crit_dmg_mult = 1.3;

	static const int bar_width = 100;
	static const int bar_height = 20;

	SDL_Rect health_rect_behind; SDL_Rect health_rect_front;
	SDL_Texture* health_text; std::string health_str; const char* health_char; SDL_Rect health_rect;

	SDL_Rect contain_rect;
	SDL_Rect current_destRect = destRect_down_2;

private: // retreive private member variables from outside classes by calling public class function that returns it (for example - getAllObjects returns objList).
	static std::vector<Enemy*> objList; // list of all objects of this class

	int max_vel = 3;

	bool up;
	bool down;
	bool left;
	bool right;
	bool stand;

	int frame = 0;
	int walking_frames = 12; // The number of frames before the updated animation renders.

	float rand_num;

	int moveLoopCount = 0;
	int moveLoopCount_Reset = 40;
	float direction;

	SDL_Texture* enemyTexture_Up_1, * enemyTexture_Up_Default, * enemyTexture_Up_3;
	SDL_Texture* enemyTexture_Down_1, * enemyTexture_Down_Default, * enemyTexture_Down_3;
	SDL_Texture* enemyTexture_Left_1, * enemyTexture_Left_Default, * enemyTexture_Left_3;
	SDL_Texture* enemyTexture_Right_1, * enemyTexture_Right_Default, * enemyTexture_Right_3;

	SDL_Rect srcRect_down_1, srcRect_down_2, srcRect_down_3, srcRect_up_1, srcRect_up_2, srcRect_up_3;
	SDL_Rect srcRect_left_1, srcRect_left_2, srcRect_left_3, srcRect_right_1, srcRect_right_2, srcRect_right_3;

	SDL_Rect destRect_down_1, destRect_down_2, destRect_down_3, destRect_up_1, destRect_up_2, destRect_up_3;
	SDL_Rect destRect_left_1, destRect_left_2, destRect_left_3, destRect_right_1, destRect_right_2, destRect_right_3;
};

#endif /* ENEMIES_H */
