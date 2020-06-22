#include "Enemies.h"
#include "Character.h"
#include "Draw.h"

/****************************************************************************************************/
Enemy::Enemy(const char* tex_down_1, const char* tex_down_default, const char* tex_down_3,
	         const char* tex_up_1, const char* tex_up_default, const char* tex_up_3,
	         const char* tex_left_1, const char* tex_left_default, const char* tex_left_3,
	         const char* tex_right_1, const char* tex_right_default, const char* tex_right_3,
	         int w_down_1, int w_down_2, int w_down_3, int w_up_1, int w_up_2, int w_up_3,
	         int w_left_1, int w_left_2, int w_left_3, int w_right_1, int w_right_2, int w_right_3,
	         int h_down_1, int h_down_2, int h_down_3, int h_up_1, int h_up_2, int h_up_3,
	         int h_left_1, int h_left_2, int h_left_3, int h_right_1, int h_right_2, int h_right_3,
	         int x, int y, int containment_left, int containment_top, int containment_w, int containment_h,
	         int dest_rect_multiple, double health_max, int threat_level)
{
	objList.push_back(this);

	enemyTexture_Down_1 = TextureManager::LoadTexture(tex_down_1);
	enemyTexture_Down_Default = TextureManager::LoadTexture(tex_down_default);
	enemyTexture_Down_3 = TextureManager::LoadTexture(tex_down_3);
	enemyTexture_Up_1 = TextureManager::LoadTexture(tex_up_1);
	enemyTexture_Up_Default = TextureManager::LoadTexture(tex_up_default);
	enemyTexture_Up_3 = TextureManager::LoadTexture(tex_up_3);
	enemyTexture_Left_1 = TextureManager::LoadTexture(tex_left_1);
	enemyTexture_Left_Default = TextureManager::LoadTexture(tex_left_default);
	enemyTexture_Left_3 = TextureManager::LoadTexture(tex_left_3);
	enemyTexture_Right_1 = TextureManager::LoadTexture(tex_right_1);
	enemyTexture_Right_Default = TextureManager::LoadTexture(tex_right_default);
	enemyTexture_Right_3 = TextureManager::LoadTexture(tex_right_3);

	down = true;
	up = false;
	left = false;
	right = false;
	stand = true;

	threat = threat_level;

	xpos = x;
	ypos = y;

	health = health_max;
	max_health = health_max;

	contain_rect.x = containment_left; contain_rect.y = containment_top; contain_rect.w = containment_w; contain_rect.h = containment_h;

	srcRect_down_1.x = 0; srcRect_down_2.x = 0; srcRect_down_3.x = 0;
	srcRect_up_1.x = 0; srcRect_up_2.x = 0; srcRect_up_3.x = 0;
	srcRect_left_1.x = 0; srcRect_left_2.x = 0; srcRect_left_3.x = 0;
	srcRect_right_1.x = 0; srcRect_right_2.x = 0; srcRect_right_3.x = 0;

	srcRect_down_1.y = 0; srcRect_down_2.y = 0; srcRect_down_3.y = 0;
	srcRect_up_1.y = 0; srcRect_up_2.y = 0; srcRect_up_3.y = 0;
	srcRect_left_1.y = 0; srcRect_left_2.y = 0; srcRect_left_3.y = 0;
	srcRect_right_1.y = 0; srcRect_right_2.y = 0; srcRect_right_3.y = 0;

	srcRect_down_1.w = w_down_1; srcRect_down_2.w = w_down_2; srcRect_down_3.w = w_down_3;
	srcRect_up_1.w = w_up_1; srcRect_up_2.w = w_up_2; srcRect_up_3.w = w_up_3;
	srcRect_left_1.w = w_left_1; srcRect_left_2.w = w_left_2; srcRect_left_3.w = w_left_3;
	srcRect_right_1.w = w_right_1; srcRect_right_2.w = w_right_2; srcRect_right_3.w = w_right_3;

	srcRect_down_1.h = h_down_1; srcRect_down_2.h = h_down_2; srcRect_down_3.h = h_down_3;
	srcRect_up_1.h = h_up_1; srcRect_up_2.h = h_up_2; srcRect_up_3.h = h_up_3;
	srcRect_left_1.h = h_left_1; srcRect_left_2.h = h_left_2; srcRect_left_3.h = h_left_3;
	srcRect_right_1.h = h_right_1; srcRect_right_2.h = h_right_2; srcRect_right_3.h = h_right_3;

	destRect_down_1.w = w_down_1 * dest_rect_multiple; destRect_down_2.w = w_down_2 * dest_rect_multiple; destRect_down_3.w = w_down_3 * dest_rect_multiple;
	destRect_up_1.w = w_up_1 * dest_rect_multiple; destRect_up_2.w = w_up_2 * dest_rect_multiple; destRect_up_3.w = w_up_3 * dest_rect_multiple;
	destRect_left_1.w = w_left_1 * dest_rect_multiple; destRect_left_2.w = w_left_2 * dest_rect_multiple; destRect_left_3.w = w_left_3 * dest_rect_multiple;
	destRect_right_1.w = w_right_1 * dest_rect_multiple; destRect_right_2.w = w_right_2 * dest_rect_multiple; destRect_right_3.w = w_right_3 * dest_rect_multiple;

	destRect_down_1.h = h_down_1 * dest_rect_multiple; destRect_down_2.h = h_down_2 * dest_rect_multiple; destRect_down_3.h = h_down_3 * dest_rect_multiple;
	destRect_up_1.h = h_up_1 * dest_rect_multiple; destRect_up_2.h = h_up_2 * dest_rect_multiple; destRect_up_3.h = h_up_3 * dest_rect_multiple;
	destRect_left_1.h = h_left_1 * dest_rect_multiple; destRect_left_2.h = h_left_2 * dest_rect_multiple; destRect_left_3.h = h_left_3 * dest_rect_multiple;
	destRect_right_1.h = h_right_1 * dest_rect_multiple; destRect_right_2.h = h_right_2 * dest_rect_multiple; destRect_right_3.h = h_right_3 * dest_rect_multiple;
}

/****************************************************************************************************/
void Enemy::Update()
{
	if (!attackLoop)
		Movement();
	else
		horizontal_path = Chase(horizontal_path);

	if (!stand)
	{
		if (up)
			ypos -= max_vel;
		else if (down)
			ypos += max_vel;
		else if (left)
			xpos -= max_vel;
		else if (right)
			xpos += max_vel;
	}

	health_rect_front = { xpos + (current_destRect.w / 2) - (bar_width / 2), ypos - 30, int(round(bar_width * health / max_health)), bar_height };
	health_rect_behind = { xpos + (current_destRect.w / 2) - (bar_width / 2), ypos - 30, bar_width, bar_height };

	destRect_down_1.x = xpos; destRect_down_2.x = xpos; destRect_down_3.x = xpos; destRect_up_1.x = xpos; destRect_up_2.x = xpos; destRect_up_3.x = xpos;
	destRect_left_1.x = xpos; destRect_left_2.x = xpos; destRect_left_3.x = xpos; destRect_right_1.x = xpos; destRect_right_2.x = xpos; destRect_right_3.x = xpos;

	destRect_down_1.y = ypos; destRect_down_2.y = ypos; destRect_down_3.y = ypos; destRect_up_1.y = ypos; destRect_up_2.y = ypos; destRect_up_3.y = ypos;
	destRect_left_1.y = ypos; destRect_left_2.y = ypos; destRect_left_3.y = ypos; destRect_right_1.y = ypos; destRect_right_2.y = ypos; destRect_right_3.y = ypos;
}

/****************************************************************************************************/
void Enemy::Render()
{
	if (up)
	{
		if (!stand)
		{
			current_destRect = Animate(enemyTexture_Up_1, enemyTexture_Up_Default, enemyTexture_Up_3);
		}
		else
		{
			SDL_RenderCopy(Game::renderer, enemyTexture_Up_Default, &srcRect_up_2, &destRect_up_2);
			frame = 0;
			current_destRect = destRect_up_2;
		}
	}
	else if (down)
	{
		if (!stand)
		{
			current_destRect = Animate(enemyTexture_Down_1, enemyTexture_Down_Default, enemyTexture_Down_3);
		}
		else
		{
			SDL_RenderCopy(Game::renderer, enemyTexture_Down_Default, &srcRect_down_2, &destRect_down_2);
			frame = 0;
			current_destRect = destRect_down_2;
		}
	}
	else if (left)
	{
		if (!stand)
		{
			current_destRect = Animate(enemyTexture_Left_1, enemyTexture_Left_Default, enemyTexture_Left_3);
		}
		else
		{
			SDL_RenderCopy(Game::renderer, enemyTexture_Left_Default, &srcRect_left_2, &destRect_left_2);
			frame = 0;
			current_destRect = destRect_left_2;
		}
	}
	else if (right)
	{
		if (!stand)
		{
			current_destRect = Animate(enemyTexture_Right_1, enemyTexture_Right_Default, enemyTexture_Right_3);
		}
		else
		{
			SDL_RenderCopy(Game::renderer, enemyTexture_Right_Default, &srcRect_right_2, &destRect_right_2);
			frame = 0;
			current_destRect = destRect_right_2;
		}
	}

	if (frame / 4 >= walking_frames) // cycle between sprites
	{
		frame = 0;
	}

	/*
	 // Do things if in range of the enemy
	if (inRange) // If close enough to an enemy, draw containment area and hitbox blue
	{
		DrawContainmentBox(0, 0, 255, 255);
		DrawHitbox(0, 0, 255, 255);
	}
	else // else draw them red
	{
		DrawContainmentBox(255, 0, 0, 255);
		DrawHitbox(255, 0, 0, 255);
	}
	*/

	if (highlighted)
		DrawHitbox(255, 0, 0, 255); // red
	if (attack_highlighted)
		DrawHitbox(0, 255, 0, 255); // green

	if (highlighted | attack_highlighted)
	{
		DrawHealthBar();
	}
}

/****************************************************************************************************/
SDL_Rect Enemy::Animate(SDL_Texture* tex_1, SDL_Texture* tex_default, SDL_Texture* tex_3)
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
void Enemy::Movement()
{
	if (moveLoopCount == 0)
	{
		direction = Game::getRandom();
	}
	// Random movement
	if (moveLoopCount < moveLoopCount_Reset)
	{
		if (direction <= 0.2) // stand
		{
			stand = true;
		}
		else if ((direction > 0.2) & (direction <= 0.4)) // up
		{
			if (ypos < contain_rect.y)
			{
				stand = true;
			}
			else
			{
				up = true;
				down = false;
				left = false;
				right = false;
				stand = false;
			}
		}
		else if ((direction > 0.4) & (direction <= 0.6)) // down
		{
			if ((ypos + destRect_down_1.h > contain_rect.y + contain_rect.h) | (ypos + destRect_down_2.h > contain_rect.y + contain_rect.h) | (ypos + destRect_down_3.h > contain_rect.y + contain_rect.h))
			{
				stand = true;
			}
			else
			{
				up = false;
				down = true;
				left = false;
				right = false;
				stand = false;
			}
		}
		else if ((direction > 0.6) & (direction <= 0.8)) // left
		{
			if (xpos < contain_rect.x)
			{
				stand = true;
			}
			else
			{
				up = false;
				down = false;
				left = true;
				right = false;
				stand = false;
			}
		}
		else if (direction > 0.8) // right
		{
			if ((xpos + destRect_right_1.w > contain_rect.x + contain_rect.w) | (xpos + destRect_right_2.w > contain_rect.x + contain_rect.w) | (xpos + destRect_right_3.w > contain_rect.x + contain_rect.w))
			{
				stand = true;
			}
			else
			{
				up = false;
				down = false;
				left = false;
				right = true;
				stand = false;
			}
		}
	}

	moveLoopCount += 1;
	if (moveLoopCount >= moveLoopCount_Reset)
	{
		moveLoopCount = 0;
	}
}

/****************************************************************************************************/
bool Enemy::Chase(bool prev_path)
{
	// Only using horizontal path bool to see whether enemy should move left/right or up/down.
	if (std::max(abs(dx), abs(dy)) == abs(dx))
	{
		horizontal_path = true;
	}
	else
	{
		horizontal_path = false;
	}
	if (abs(abs(dx) - abs(dy)) < chase_buffer)
	{
		horizontal_path = prev_path;
	}

	for (int i = 0; i < Character::getAllObjects().size(); i++) // just player object
	{
		if (horizontal_path)
		{
			if (dx > (Character::getAllObjects()[i]->current_destRect.w / 2) + (current_destRect.w / 2) - path_offset1) // Player to the left, so enemy moves left
			{
				//std::cout << "Player left" << std::endl;
				if (xpos > contain_rect.x)
				{
					up = false;
					down = false;
					left = true;
					right = false;
					stand = false;
				}
				else
				{
					stand = true;
					attackLoop = false;
					frame = 0;
				}
			}
			else if (dx < -((Character::getAllObjects()[i]->current_destRect.w / 2) + (current_destRect.w / 2) - path_offset1)) // Player to the right, so enemy moves right
			{
				//std::cout << "Player right" << std::endl;
				if (xpos + current_destRect.w < contain_rect.x + contain_rect.w)
				{
					up = false;
					down = false;
					left = false;
					right = true;
					stand = false;
				}
				else
				{
					stand = true;
					attackLoop = false;
					frame = 0;
				}
			}
			else if ((dx >= 0) & (dx <= (Character::getAllObjects()[i]->current_destRect.w / 2) + (current_destRect.w / 2))) // Player to the left, but close. Attack once this close
			{
				if ((dy > (Character::getAllObjects()[i]->current_destRect.h / 2) + (current_destRect.h / 2) + path_offset2) | (dy < -((Character::getAllObjects()[i]->current_destRect.h / 2) + (current_destRect.h / 2) - path_offset3)))
				{
					//std::cout << "Player left -> vertical" << std::endl;
					horizontal_path = false;
				}
				else
				{
					//std::cout << "Player left close" << std::endl;
					up = false;
					down = false;
					left = true;
					right = false;
					stand = true;
					frame = 0;
				}
			}
			else if ((dx < 0) & (dx >= -((Character::getAllObjects()[i]->current_destRect.w / 2) + (current_destRect.w / 2)))) // Player to the right, but close. Attack once this close
			{
				if ((dy > (Character::getAllObjects()[i]->current_destRect.h / 2) + (current_destRect.h / 2) + path_offset2) | (dy < -((Character::getAllObjects()[i]->current_destRect.h / 2) + (current_destRect.h / 2) - path_offset3)))
				{
					//std::cout << "Player right -> vertical" << std::endl;
					horizontal_path = false;
				}
				else
					//std::cout << "Player right close" << std::endl;
				{
					up = false;
					down = false;
					left = false;
					right = true;
					stand = true;
					frame = 0;
				}
			}
		}
		else // if vertical path...
		{
			if (dy > (Character::getAllObjects()[i]->current_destRect.h / 2) + (current_destRect.h / 2) - path_offset1) // Player above, so enemy moves up
			{
				//std::cout << "Player above" << std::endl;
				if (ypos > contain_rect.y)
				{
					up = true;
					down = false;
					left = false;
					right = false;
					stand = false;
				}
				else
				{
					stand = true;
					attackLoop = false;
					frame = 0;
				}
			}
			else if (dy < -((Character::getAllObjects()[i]->current_destRect.h / 2) + (current_destRect.h / 2) - path_offset1)) // Player below, so enemy moves down
			{
				//std::cout << "Player below" << std::endl;
				if (ypos + current_destRect.h < contain_rect.y + contain_rect.h)
				{
					up = false;
					down = true;
					left = false;
					right = false;
					stand = false;
				}
				else
				{
					stand = true;
					attackLoop = false;
					frame = 0;
				}
			}
			else if ((dy >= 0) & (dy <= (Character::getAllObjects()[i]->current_destRect.h / 2) + (current_destRect.h / 2))) // Player above, but close. Attack once this close
			{
				if ((dx >= (Character::getAllObjects()[i]->current_destRect.w / 2) + (current_destRect.w / 2) + path_offset2) | (dx <= -((Character::getAllObjects()[i]->current_destRect.w / 2) + (current_destRect.w / 2) + path_offset2)))
				{
					//std::cout << "Player above -> horizontal" << std::endl;
					horizontal_path = true;
				}
				else
				{
					//std::cout << "Player above close" << std::endl;
					up = true;
					down = false;
					left = false;
					right = false;
					stand = true;
					frame = 0;
				}
			}
			else if ((dy < 0) & (dy >= -((Character::getAllObjects()[i]->current_destRect.h / 2) + (current_destRect.h / 2)))) // Player below, but close. Attack once this close
			{
				if ((dx >= (Character::getAllObjects()[i]->current_destRect.w / 2) + (current_destRect.w / 2) + path_offset2) | (dx <= -((Character::getAllObjects()[i]->current_destRect.w / 2) + (current_destRect.w / 2) + path_offset5)))
				{
					//std::cout << "Player below -> horizontal" << std::endl;
					horizontal_path = true;
				}
				else
				{
					//std::cout << "Player below close" << std::endl;
					up = false;
					down = true;
					left = false;
					right = false;
					stand = true;
					frame = 0;
				}
			}
		}
		if (stand) // If close enough to no longer chase the player, enemy can attack.
		{
			if (!damageLoop)
			{
				if (initialAttack)
				{
					attack();
					initialAttack = false;
				}
				else
				{
					attack_timer = SDL_AddTimer(2000, attack_callback, this); // After 2 seconds, call attack function for this object.
				}
				damageLoop = !damageLoop; // Acts as a switch to turn off calling the attack function until 2 seconds have passed.
			}
		}
		else
		{
			if (!initialAttack)
			{
				if (initialSwitch)
				{
					initAttackCoolDown_timer = SDL_AddTimer(2000, initAttackCoolDown_callback, this); // After 2 seconds, call initAttackCoolDown function for this object.
					initialSwitch = false; // Prevents repeated calling of initAttackCooldown.
				}
			}
		}
	}

	return horizontal_path;
}

/****************************************************************************************************/
void Enemy::attack()
{
	if (health > 0)
	{
		for (int i = 0; i < Character::getAllObjects().size(); i++) // Just player object
		{
			if (DistanceToPlayer() < sqrt(pow((Character::getAllObjects()[i]->current_destRect.w / 2) + (current_destRect.w / 2) + 50, 2) + pow((Character::getAllObjects()[i]->current_destRect.h / 2) + (current_destRect.h / 2) + 50, 2)))
			{
				if (Character::getAllObjects()[i]->health > 0)
				{
					Character::getAllObjects()[i]->health -= base_dmg;
					Character::getAllObjects()[i]->health = std::max(double(0), Character::getAllObjects()[i]->health);
				}
			}
		}
		damageLoop = !damageLoop;
	}
}

/****************************************************************************************************/
Uint32 Enemy::attack_callback(Uint32 interval, void* param) // Call attack function after 2 seconds
{
	// Passing "this" as param, which is the specific enemy object that is attacking. Need this object to call nonstatic attack function.
	SDL_Event event;

	event.type = SDL_USEREVENT;
	event.user.code = BASE_ATTACK;
	event.user.data1 = param;
	event.user.data2 = NULL;

	SDL_PushEvent(&event);

	return 0; // Only fire once every time this is called. Return interval if repeating.
}

/****************************************************************************************************/
void Enemy::initAttackCoolDown()
{
	initialAttack = true;
	initialSwitch = true;
}

/****************************************************************************************************/
Uint32 Enemy::initAttackCoolDown_callback(Uint32 interval, void* param) // Call initAttackCoolDown function after 2 seconds
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
std::vector<Enemy*> Enemy::getAllObjects()
{
	return objList;
}

/****************************************************************************************************/
void Enemy::MoveObjectsDown(int max_vel)
{
	for (int i = 0; i < getAllObjects().size(); i++)
	{
		getAllObjects()[i]->ypos += max_vel;
		getAllObjects()[i]->contain_rect.y += max_vel;
	}
}

/****************************************************************************************************/
void Enemy::MoveObjectsUp(int max_vel)
{
	for (int i = 0; i < getAllObjects().size(); i++)
	{
		getAllObjects()[i]->ypos -= max_vel;
		getAllObjects()[i]->contain_rect.y -= max_vel;
	}
}

/****************************************************************************************************/
void Enemy::MoveObjectsLeft(int max_vel)
{
	for (int i = 0; i < getAllObjects().size(); i++)
	{
		getAllObjects()[i]->xpos -= max_vel;
		getAllObjects()[i]->contain_rect.x -= max_vel;
	}
}

/****************************************************************************************************/
void Enemy::MoveObjectsRight(int max_vel)
{
	for (int i = 0; i < getAllObjects().size(); i++)
	{
		getAllObjects()[i]->xpos += max_vel;
		getAllObjects()[i]->contain_rect.x += max_vel;
	}
}

/****************************************************************************************************/
void Enemy::UpdateAll()
{
	for (int i = 0; i < getAllObjects().size(); i++)
	{
		getAllObjects()[i]->Update();
	}
}

/****************************************************************************************************/
void Enemy::RenderAll()
{
	for (int i = 0; i < getAllObjects().size(); i++)
	{
		getAllObjects()[i]->Render();
	}
}

/****************************************************************************************************/
void Enemy::xDistanceToPlayer()
{
	// Dx, Dy are vectors from player to enemy (i.e. enemy pos - player pos)
	for (int i = 0; i < Character::getAllObjects().size(); i++) // just player object
	{
		dx = ((xpos + (current_destRect.w / 2)) - (Character::getAllObjects()[i]->xpos + (Character::getAllObjects()[i]->current_destRect.w / 2)));
	}
}

/****************************************************************************************************/
void Enemy::yDistanceToPlayer()
{
	// Dx, Dy are vectors from player to enemy (i.e. enemy pos - player pos), center to center
	for (int i = 0; i < Character::getAllObjects().size(); i++) // just player object
	{
		dy = ((ypos + (current_destRect.h / 2)) - (Character::getAllObjects()[i]->ypos + (Character::getAllObjects()[i]->current_destRect.h / 2)));
	}
}

/****************************************************************************************************/
double Enemy::DistanceToPlayer()
{
	for (int i = 0; i < Character::getAllObjects().size(); i++) // just player object
	{
		return DistCalc(Character::getAllObjects()[i]->xpos, Character::getAllObjects()[i]->ypos, 
			            Character::getAllObjects()[i]->current_destRect.w, Character::getAllObjects()[i]->current_destRect.h,
			            xpos, ypos, current_destRect.w, current_destRect.h);
	}
}

/****************************************************************************************************/
double Enemy::DistCalc(int player_x, int player_y, int player_w, int player_h, int enemy_x, int enemy_y, int enemy_w, int enemy_h)
{
	return sqrt(pow(((enemy_x + (enemy_w / 2)) - (player_x + (player_w / 2))), 2) + pow(((enemy_y + (enemy_h / 2)) - (player_y + (player_h / 2))), 2));
}

/****************************************************************************************************/
void Enemy::AllDistancesToPlayer()
{
	for (int i = 0; i < getAllObjects().size(); i++)
		distances.push_back(getAllObjects()[i]->DistanceToPlayer());
}

/****************************************************************************************************/
void Enemy::ClearHighlights()
{
	for (int i = 0; i < getAllObjects().size(); i++)
	{
		getAllObjects()[i]->highlighted = false;
		getAllObjects()[i]->attack_highlighted = false;
	}
}

/****************************************************************************************************/
bool Enemy::AnyHighlighted(bool attack_highlight, bool highlight)
{
	int highlighted_count = 0;
	if (attack_highlight & highlight)
	{
		for (int i = 0; i < getAllObjects().size(); i++)
		{
			if ((getAllObjects()[i]->highlighted) | (getAllObjects()[i]->attack_highlighted))
				highlighted_count++;
		}
	}
	else if (attack_highlight & (!highlight))
	{
		for (int i = 0; i < getAllObjects().size(); i++)
		{
			if (getAllObjects()[i]->attack_highlighted)
				highlighted_count++;
		}
	}
	else if ((!attack_highlight) & highlight)
	{
		for (int i = 0; i < getAllObjects().size(); i++)
		{
			if (getAllObjects()[i]->highlighted)
				highlighted_count++;
		}
	}
	if (highlighted_count > 0)
		return true;
	else
		return false;
}

/****************************************************************************************************/
int Enemy::AttackHighlightedEnemy()
{
	for (int i = 0; i < getAllObjects().size(); i++)
	{
		if (getAllObjects()[i]->attack_highlighted)
		{
			return i; // return's the i'th enemy in Enemy::objList
			break;
		}
	}
}

/****************************************************************************************************/
void Enemy::DrawContainmentBox(int r, int g, int b, int a)
{
	SDL_SetRenderDrawColor(Game::renderer, r, g, b, a); // set render draw color
	SDL_RenderDrawRect(Game::renderer, &contain_rect); // render containment area
	SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255); // reset render draw color
}

/****************************************************************************************************/
void Enemy::DrawHitbox(int r, int g, int b, int a)
{
	SDL_SetRenderDrawColor(Game::renderer, r, g, b, a); // set render draw color
	SDL_RenderDrawRect(Game::renderer, &current_destRect); // render current frame hitbox
	SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255); // reset render draw color
}

/****************************************************************************************************/
void Enemy::DrawHealthBar()
{
	TextureManager::DrawFilledBox(health_rect_behind, 200, 0, 0, 255);
	TextureManager::DrawFilledBox(health_rect_front, 0, 200, 0, 255);

	health_str = std::to_string(int(round(100 * health / max_health))) + std::string("%");
	health_char = health_str.c_str();
	int health_width; int health_height;
	for (int i = 0; i < Character::getAllObjects().size(); i++) // just player object
	{
		health_text = TextureManager::LoadText(Character::getAllObjects()[i]->stats_font, health_char, { 0,0,0 });
		TTF_SizeText(Character::getAllObjects()[i]->stats_font, health_char, &health_width, &health_height);
	}
	health_rect.w = health_width;
	health_rect.h = health_height;
	health_rect.x = xpos + (current_destRect.w / 2) - (health_width / 2);
	health_rect.y = ypos - 30 + (bar_height / 2) - (health_height / 2);
	SDL_RenderCopy(Game::renderer, health_text, NULL, &health_rect);
}