#include "Game.h"
#include "Character.h"
#include "Draw.h"

Game* game = nullptr;

int main(int argc, char* argv[])
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();
	game->init("My First Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Game::screenWidth, Game::screenHeight, true);

	bool main_menu = true;
	bool class_menu = true;

	while (main_menu) // Title Screen
	{
		//single-press keys and mouse
		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT: // Pressed X at top right of screen.
			// Eventually ask "Are you sure you would like to quit?" and click yes or no.
			main_menu = false;
			game->isRunning = false;
			break;

		case SDL_KEYDOWN:
			if (event.key.repeat == 0)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					// Eventually ask "Are you sure you would like to quit?" and click yes or no.
					main_menu = false;
					game->isRunning = false;
				}
				else if (event.key.keysym.sym == SDLK_RETURN)
				{
					main_menu = false;
				}
			}
			break;
		}

		SDL_RenderClear(Game::renderer);
		SDL_RenderCopy(Game::renderer, game->title_text, NULL, &game->title_rect);
		SDL_RenderCopy(Game::renderer, game->enter_text, NULL, &game->enter_rect);
		SDL_RenderPresent(Game::renderer);
	}
	TTF_CloseFont(game->title_font);
	TTF_CloseFont(game->enter_font);

	game->class_render();

	while (class_menu) // Class Selection Screen
	{
		//single-press keys and mouse
		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT: // Pressed X at top right of screen.
			// Eventually ask "Are you sure you would like to quit?" and click yes or no.
			class_menu = false;
			game->isRunning = false;
			break;

		case SDL_KEYDOWN:
			if (event.key.repeat == 0)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					// Eventually ask "Are you sure you would like to quit?" and click yes or no.
					class_menu = false;
					game->isRunning = false;
				}
				else if (event.key.keysym.sym == SDLK_1)
				{
					game->class_init(1);
					class_menu = false;
				}
				else if (event.key.keysym.sym == SDLK_2)
				{
					game->class_init(2);
					class_menu = false;
				}
				else if (event.key.keysym.sym == SDLK_3)
				{
					game->class_init(3);
					class_menu = false;
				}
				else if (event.key.keysym.sym == SDLK_4)
				{
					game->class_init(4);
					class_menu = false;
				}
				else if (event.key.keysym.sym == SDLK_5)
				{
					game->class_init(5);
					class_menu = false;
				}
				else if (event.key.keysym.sym == SDLK_6)
				{
					game->class_init(6);
					class_menu = false;
				}
			}
			break;
		}

		SDL_RenderClear(Game::renderer);
		SDL_RenderCopy(Game::renderer, game->class_text, NULL, &game->class_rect);
		SDL_RenderCopy(Game::renderer, game->warrior_text, NULL, &game->warrior_rect);
		SDL_RenderCopy(Game::renderer, game->rogue_text, NULL, &game->rogue_rect);
		SDL_RenderCopy(Game::renderer, game->predator_text, NULL, &game->predator_rect);
		SDL_RenderCopy(Game::renderer, game->mystic_text, NULL, &game->mystic_rect);
		SDL_RenderCopy(Game::renderer, game->cultist_text, NULL, &game->cultist_rect);
		SDL_RenderCopy(Game::renderer, game->priest_text, NULL, &game->priest_rect);
		SDL_RenderCopy(Game::renderer, game->warrior_text2, NULL, &game->warrior_rect2);
		SDL_RenderCopy(Game::renderer, game->rogue_text2, NULL, &game->rogue_rect2);
		SDL_RenderCopy(Game::renderer, game->predator_text2, NULL, &game->predator_rect2);
		SDL_RenderCopy(Game::renderer, game->mystic_text2, NULL, &game->mystic_rect2);
		SDL_RenderCopy(Game::renderer, game->cultist_text2, NULL, &game->cultist_rect2);
		SDL_RenderCopy(Game::renderer, game->priest_text2, NULL, &game->priest_rect2);
		SDL_RenderPresent(Game::renderer);
	}

	while (game->running()) // Game Loop
	{
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();

	return 0;
}