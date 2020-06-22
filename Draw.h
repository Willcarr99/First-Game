#ifndef DRAW_H
#define DRAW_H

#include "SDL_image.h"
#include "Game.h"

/****************************************************************************************************/
class MapObject {

public:
	MapObject(const char* asset, int x, int y, int w, int h, int dest_rect_mult);
	~MapObject();

	static std::vector<MapObject*> getAllObjects();

	static void DrawAllObjects();
	static void MoveObjectsDown(int max_vel);
	static void MoveObjectsUp(int max_vel);
	static void MoveObjectsLeft(int max_vel);
	static void MoveObjectsRight(int max_vel);

private:
	static std::vector<MapObject*> objList; // list of all objects of this class

	SDL_Rect src, dest;

	SDL_Texture* tex;
};

/****************************************************************************************************/
class Map {

public:
	Map();
	~Map();

	static std::vector<Map*> getAllObjects();

	static const int map_scale = 6; // 1 originally. Setting this higher no longer makes things laggy because only drawing neighbor chunks. Can have big maps with no lag!
	static const int tile_size = 20; // Make sure it's divisbile by screenWidth and screenHeight
	static const int num_tiles_screenWidth = Game::screenWidth / tile_size;
	static const int num_tiles_screenHeight = Game::screenHeight / tile_size;
	static const int num_chunks_w = 2 * map_scale; // 2 ----- number of chunks the map contains (1 chunk = screen size (1600, 900)). Assumed to be even numbers
	static const int num_chunks_h = 2 * map_scale; // 2

	int current_chunk;
	std::vector<int> neighbor_chunks;
	int num_inaccessible_segments;
	std::vector<std::vector<int>> inaccessible_segments_x; // vector of vectors. Each element is a vector of either x or y inaccessible tile coords
	std::vector<std::vector<int>> inaccessible_segments_y;
	std::vector<int> inaccessible_segment_centers_x;
	std::vector<int> inaccessible_segment_centers_y;
	std::vector<int> inaccessible_segment_radii;
	std::vector<int> inaccessible_tile_types;

	void CreateMap(int level[num_chunks_h * num_tiles_screenHeight][num_chunks_w * num_tiles_screenWidth]);
	void CreateMapSegment(int level[num_chunks_h * num_tiles_screenHeight][num_chunks_w * num_tiles_screenWidth], double map_frac_start_w, double map_frac_end_w, double map_frac_start_h, double map_frac_end_h, bool accessible, int tile_type);
	void CreateCircle(int level[num_chunks_h * num_tiles_screenHeight][num_chunks_w * num_tiles_screenWidth], double map_frac_start_w, double map_frac_start_h, double rad, bool accessible, int tile_type);
	void LoadMap(int arr[num_chunks_h * num_tiles_screenHeight][num_chunks_w * num_tiles_screenWidth]);
	void GetInaccessibleTileCoords();
	void GetCurrentTileType();
	void GetCurrentChunk();
	void GetNeighborChunks();
	void DrawNeighborChunks();
	void DrawFullMap();
	void ClearDrawVectors();

	int map_x_start;
	int map_y_start;
	int map_x;
	int map_y;

private:
	static std::vector<Map*> objList; // list of all objects of this class

	SDL_Rect src, dest;
	SDL_Texture* dirt;
	SDL_Texture* grass;
	SDL_Texture* water;

	int lvl1[num_chunks_h * num_tiles_screenHeight][num_chunks_w * num_tiles_screenWidth];
	int inaccessible_tiles[num_chunks_h * num_tiles_screenHeight][num_chunks_w * num_tiles_screenWidth]; // Each segment with inaccessible tiles has a different number
	int map[num_chunks_h * num_tiles_screenHeight][num_chunks_w * num_tiles_screenWidth];

};

/****************************************************************************************************/
class TextureManager {

public:
	static SDL_Texture* LoadTexture(const char* fileName);
	static SDL_Texture* LoadText(TTF_Font* font, const char* text, SDL_Color color);
	static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
	static void DrawLine(int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	static void DrawFilledBox(SDL_Rect rect, int r, int g, int b, int a);
};

/****************************************************************************************************/
#endif /* DRAW_H */
