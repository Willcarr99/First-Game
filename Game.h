#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "SDL.h"
#include "SDL_ttf.h"
#include <random>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <cmath>
#include <string>

class Game {

public: /* Publically available to other classes */

	Game(); /* Constructor constructs the Game object */
	~Game(); /* Deconstructor for when we close it */

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void class_init(int index);
	void class_render();
	void handleEvents();
	void update();
	void render();
	void clean();
	bool running();
	static double getRandom();

	static const int screenWidth = 1600;
	static const int screenHeight = 900;

	int mouse_x;
	int mouse_y;

	static SDL_Renderer* renderer;
	const Uint8* keystate;

	TTF_Font* title_font;
	SDL_Texture* title_text;
	SDL_Rect title_rect;

	TTF_Font* enter_font;
	SDL_Texture* enter_text;
	SDL_Rect enter_rect;

	TTF_Font* class_font;
	SDL_Texture* class_text;
	SDL_Rect class_rect;
	SDL_Texture* warrior_text;
	SDL_Rect warrior_rect;
	SDL_Texture* warrior_text2;
	SDL_Rect warrior_rect2;
	SDL_Texture* rogue_text;
	SDL_Rect rogue_rect;
	SDL_Texture* rogue_text2;
	SDL_Rect rogue_rect2;
	SDL_Texture* predator_text;
	SDL_Rect predator_rect;
	SDL_Texture* predator_text2;
	SDL_Rect predator_rect2;
	SDL_Texture* mystic_text;
	SDL_Rect mystic_rect;
	SDL_Texture* mystic_text2;
	SDL_Rect mystic_rect2;
	SDL_Texture* cultist_text;
	SDL_Rect cultist_rect;
	SDL_Texture* cultist_text2;
	SDL_Rect cultist_rect2;
	SDL_Texture* priest_text;
	SDL_Rect priest_rect;
	SDL_Texture* priest_text2;
	SDL_Rect priest_rect2;

	bool isRunning;

	int class_index;

private:

	int counter = 0;
	int highlight_count = 0;
	SDL_Window* window;

};

#endif /* GAME_H */
