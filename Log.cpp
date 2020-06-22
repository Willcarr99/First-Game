#include "Log.h"
#include "Draw.h"

/****************************************************************************************************/
// Log Methods
/****************************************************************************************************/

Log::Log(const char* log_surface)
{
	objList.push_back(this);

	logTexture_surface = TextureManager::LoadTexture(log_surface);

	log_font = TTF_OpenFont("assets/fonts/OpenSans-Regular.ttf", 12);

	logLoop = false;

	logText_srcRect.w = 0; logText_srcRect.h = 0;
	logText_srcRect.x = logText_srcRect.y = 0;

	scrollBar_x = logSurface_rect.x + logSurface_rect.w - 10;
	scrollBar_y = logSurface_rect.y + logSurface_rect.h - 50; // Initial value. Changes based on upCount and logHistoryList.size().

	logDisplay_it = logDisplayList.begin();
	logHistory_it = logHistoryList.begin();
}

/****************************************************************************************************/
void Log::LogStore(std::vector<std::string> log_lines)
{
	for (std::string line : log_lines)
	{
		if (upCount == 0)
			logDisplay_it = logDisplayList.insert(logDisplay_it, line);
		else if (upCount > 0)
			upCount += 1;
		logHistory_it = logHistoryList.insert(logHistory_it, line);
	}
	lineCount += log_lines.size();

	while (lineCount > 7)
	{
		if (upCount == 0)
			logDisplayList.pop_back(); // Delete the oldest line in the log.
		lineCount -= 1;
	}
}

/****************************************************************************************************/
void Log::LogClear()
{
	lineCount = 0;
	upCount = 0;
	logDisplayList.clear();
	logHistoryList.clear();
	logDisplay_it = logDisplayList.begin();
	logHistory_it = logHistoryList.begin();
}

/****************************************************************************************************/
void Log::LogRenderSurface()
{
	SDL_RenderCopy(Game::renderer, logTexture_surface, NULL, &logSurface_rect);
}

/****************************************************************************************************/
void Log::LogRenderText()
{
	if (logDisplayList.size() > 0)
	{
		int mult = 0;
		for (std::string line : logDisplayList)
		{
			log_text = TextureManager::LoadText(log_font, line.c_str(), { 255,255,255 });
			int log_width; int log_height; TTF_SizeText(log_font, line.c_str(), &log_width, &log_height);
			logText_rect.w = log_width;
			logText_rect.h = log_height;
			logText_rect.x = logtext_x;
			logText_rect.y = logtext_y - (mult * logtext_sep) - logText_rect.h;

			SDL_RenderCopy(Game::renderer, log_text, NULL, &logText_rect);

			mult += 1;
		}
		// Draw a scroll bar indicating the position of the displayed feed relative to the bottom (current feed), just like most scrolling text displays
		if (logHistoryList.size() == 7)
			scrollBar_y = logSurface_rect.y + logSurface_rect.h - 50;
		else
			scrollBar_y = logSurface_rect.y + logSurface_rect.h - (50 + (upCount * (logSurface_rect.h - 60) / (logHistoryList.size() - 7)));
		TextureManager::DrawLine(scrollBar_x, scrollBar_y, scrollBar_x, scrollBar_y + 40, 255, 255, 255, 255);
	}
}

/****************************************************************************************************/
void Log::LogScroll(bool wheel_up)
{
	if (lineCount == 7)
	{
		std::vector<std::string> logHistoryList_last(logHistoryList.end() - 7, logHistoryList.end());
		std::vector<std::string> logHistoryList_first(logHistoryList.begin(), logHistoryList.begin() + 7);

		if ((wheel_up) & (logDisplayList != logHistoryList_last)) // Top B.C.
		{
			upCount += 1;
			std::vector<std::string> logDisplayList_new(logHistoryList.begin() + upCount, logHistoryList.begin() + upCount + 7);
			logDisplayList = logDisplayList_new;
			logDisplay_it = logDisplayList.begin();
		}
		else if ((!wheel_up) & (logDisplayList != logHistoryList_first)) // Bottom B.C.
		{
			upCount -= 1;
			std::vector<std::string> logDisplayList_new(logHistoryList.begin() + upCount, logHistoryList.begin() + upCount + 7);
			logDisplayList = logDisplayList_new;
			logDisplay_it = logDisplayList.begin();
		}
	}
}

/****************************************************************************************************/
std::vector<Log*> Log::getAllObjects()
{
	return objList;
}

/****************************************************************************************************/