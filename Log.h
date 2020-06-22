#ifndef LOG_H
#define LOG_H

//#include "SDL_image.h"
#include "Game.h"

/****************************************************************************************************/
class Log {

public:
	Log(const char* log_surface);
	~Log();

	static std::vector<Log*> getAllObjects();

	void LogStore(std::vector<std::string> log_lines);
	void LogClear();
	void LogRenderSurface();
	void LogRenderText();
	void LogScroll(bool wheel_up);

	std::vector<std::string> logDisplayList;

	std::vector<std::string>::iterator logDisplay_it;
	std::vector<std::string>::iterator logHistory_it;

	bool logLoop;

	TTF_Font* log_font;

	int scrollBar_x;
	int scrollBar_y;

	SDL_Rect logSurface_rect = { 22, Game::screenHeight - 242, 475, 214 };
	SDL_Rect logText_srcRect;

private:
	static std::vector<Log*> objList; // list of all objects of this class

	int lineCount = 0;
	int upCount = 0;

	int logtext_x = 30;
	int logtext_y = Game::screenHeight - 35;
	int logtext_sep = 30;

	std::vector<std::string> logHistoryList;

	SDL_Texture* logTexture_surface;
	SDL_Texture* log_text;

	SDL_Rect logText_rect;
};

#endif /* LOG_H */
