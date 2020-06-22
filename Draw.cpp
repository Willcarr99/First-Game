#include "Draw.h"
#include "Character.h"

/****************************************************************************************************/
// TextureManager Class
/****************************************************************************************************/

SDL_Texture* TextureManager::LoadTexture(const char* texture)
{
	SDL_Surface* tempSurface = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return tex;
}

/****************************************************************************************************/
SDL_Texture* TextureManager::LoadText(TTF_Font* font, const char* text, SDL_Color color)
{
	SDL_Surface* messageSurface = TTF_RenderText_Solid(font, text, color);
	SDL_Texture* message = SDL_CreateTextureFromSurface(Game::renderer, messageSurface);
	SDL_FreeSurface(messageSurface);

	return message;
}

/****************************************************************************************************/
void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest)
{
	SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}

/****************************************************************************************************/
void TextureManager::DrawLine(int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_SetRenderDrawColor(Game::renderer, r, g, b, a);
	SDL_RenderDrawLine(Game::renderer, x1, y1, x2, y2);
	SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
}

/****************************************************************************************************/
void TextureManager::DrawFilledBox(SDL_Rect rect, int r, int g, int b, int a)
{
	SDL_SetRenderDrawColor(Game::renderer, r, g, b, a); // set render draw color
	SDL_RenderFillRect(Game::renderer, &rect);
	SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255); // reset render draw color
}

/****************************************************************************************************/
// MapObject Class
/****************************************************************************************************/

MapObject::MapObject(const char* asset, int x, int y, int w, int h, int dest_rect_mult)
{
	objList.push_back(this);

	tex = TextureManager::LoadTexture(asset);

	src.x = src.y = 0; src.w = w; src.h = h;
	dest.x = x; dest.y = y; dest.w = w * dest_rect_mult; dest.h = h * dest_rect_mult;
}

/****************************************************************************************************/
void MapObject::DrawAllObjects()
{
	for (int i = 0; i < getAllObjects().size(); i++)
		TextureManager::Draw(getAllObjects()[i]->tex, getAllObjects()[i]->src, getAllObjects()[i]->dest);
}

/****************************************************************************************************/
void MapObject::MoveObjectsDown(int max_vel)
{
	for (int i = 0; i < getAllObjects().size(); i++)
		getAllObjects()[i]->dest.y += max_vel;
}

/****************************************************************************************************/
void MapObject::MoveObjectsUp(int max_vel)
{
	for (int i = 0; i < getAllObjects().size(); i++)
		getAllObjects()[i]->dest.y -= max_vel;
}

/****************************************************************************************************/
void MapObject::MoveObjectsLeft(int max_vel)
{
	for (int i = 0; i < getAllObjects().size(); i++)
		getAllObjects()[i]->dest.x -= max_vel;
}

/****************************************************************************************************/
void MapObject::MoveObjectsRight(int max_vel)
{
	for (int i = 0; i < getAllObjects().size(); i++)
		getAllObjects()[i]->dest.x += max_vel;
}
/****************************************************************************************************/
std::vector<MapObject*> MapObject::getAllObjects()
{
	return objList;
}

/****************************************************************************************************/
// Map Class
/****************************************************************************************************/

// Eventually load map from external file.
// Initial chunk will have (0,0) at top left of starting screen, with player spawning (and remaining) at the center, while map and other objects move behind.

/****************************************************************************************************/
Map::Map()
{
	objList.push_back(this);

	dirt = TextureManager::LoadTexture("assets/dirt.png"); // 0
	grass = TextureManager::LoadTexture("assets/grass.png"); // 1
	water = TextureManager::LoadTexture("assets/water.png"); // 2

	map_x_start = -((num_chunks_w / 2) * Game::screenWidth);
	map_y_start = -((num_chunks_h / 2) * Game::screenHeight);
	map_x = map_x_start;
	map_y = map_y_start;

	num_inaccessible_segments = 0;
	inaccessible_tiles[num_chunks_h * num_tiles_screenHeight][num_chunks_w * num_tiles_screenWidth] = { 0 };

	CreateMap(lvl1);
	LoadMap(lvl1);

	GetInaccessibleTileCoords();

	src.x = 0;
	src.y = 0;
	src.w = dest.w = tile_size;
	src.h = dest.h = tile_size;
	dest.x = 0;
	dest.y = 0;
}

/****************************************************************************************************/
void Map::CreateMap(int level[num_chunks_h * num_tiles_screenHeight][num_chunks_w * num_tiles_screenWidth])
{
	CreateMapSegment(level, 0, 1, 0, 1, true, 0);
	CreateMapSegment(level, 0, 0.2, 0, 0.2, true, 1);
	CreateMapSegment(level, 0.8, 1, 0, 0.2, true, 1);
	CreateMapSegment(level, 0, 0.2, 0.8, 1, true, 1);
	CreateMapSegment(level, 0.8, 1, 0.8, 1, true, 1);
	CreateCircle(level, 0.52, 0.40, 30.0, false, 2);

	// Testing inaccessible areas
	
	CreateCircle(level, 0.10, 0.55, 10.0, false, 2);
	CreateCircle(level, 0.20, 0.55, 10.0, false, 2);
	CreateCircle(level, 0.30, 0.55, 10.0, false, 2);
	CreateCircle(level, 0.40, 0.55, 10.0, false, 2);
	CreateCircle(level, 0.50, 0.55, 10.0, false, 2);

	CreateMapSegment(level, 0.1, 0.15, 0.4, 0.45, false, 1);
	CreateMapSegment(level, 0.2, 0.25, 0.4, 0.45, false, 1);
	CreateMapSegment(level, 0.3, 0.35, 0.4, 0.45, false, 1);
	CreateMapSegment(level, 0.4, 0.45, 0.4, 0.45, false, 1);
	CreateMapSegment(level, 0.5, 0.55, 0.4, 0.45, false, 1);
	
}

/****************************************************************************************************/
void Map::CreateMapSegment(int level[num_chunks_h * num_tiles_screenHeight][num_chunks_w * num_tiles_screenWidth], double map_frac_start_w, double map_frac_end_w, double map_frac_start_h, double map_frac_end_h, bool accessible, int tile_type)
{
	// Create a map segment given the level, the fraction of the map size to start and end for both width and height, and the tile type as an integer
	// 0 - dirt, 1 - grass, 2 - water
	// Map already scaled with map_scale in num_chunks_w

	for (int i = int(num_tiles_screenWidth * num_chunks_w * map_frac_start_w); i < int(num_tiles_screenWidth * num_chunks_w * map_frac_end_w); i++) // number of tiles to draw along width as a fraction of total number in map width
	{
		for (int j = int(num_tiles_screenHeight * num_chunks_h * map_frac_start_h); j < int(num_tiles_screenHeight * num_chunks_h * map_frac_end_h); j++) // number of tiles to draw along height as a fraction of total number in map height
		{
			level[j][i] = tile_type;
			if (!accessible)
			{
				// Only outermost tiles contribute to inaccessible_tiles
				if ((i == int(num_tiles_screenWidth * num_chunks_w * map_frac_start_w)) or (i == int(num_tiles_screenWidth * num_chunks_w * map_frac_end_w) - 1) or (j == int(num_tiles_screenHeight * num_chunks_h * map_frac_start_h)) or (j == int(num_tiles_screenHeight * num_chunks_h * map_frac_end_h) - 1))
				{
					inaccessible_tiles[j][i] = num_inaccessible_segments + 1;
				}
			}
		}
	}
	if (!accessible)
	{
		int center_x_tile = int(ceil((int(num_tiles_screenWidth * num_chunks_w * map_frac_start_w) + int(num_tiles_screenWidth * num_chunks_w * map_frac_end_w)) / 2));
		int center_y_tile = int(ceil((int(num_tiles_screenHeight * num_chunks_h * map_frac_start_h) + int(num_tiles_screenHeight * num_chunks_h * map_frac_end_h)) / 2));
		int center_x = (center_x_tile * tile_size) + map_x;
		int center_y = (center_y_tile * tile_size) + map_y;
		int radius_x = int(ceil((int(num_tiles_screenWidth * num_chunks_w * map_frac_end_w) - int(num_tiles_screenWidth * num_chunks_w * map_frac_start_w)) / 2)) * tile_size;
		int radius_y = int(ceil((int(num_tiles_screenHeight * num_chunks_h * map_frac_end_h) - int(num_tiles_screenHeight * num_chunks_h * map_frac_start_h)) / 2)) * tile_size;
		// Making the "radius" of the inaccessible segment be 3 more tile_sizes than the circle that encloses the segment.
		int radius = int(ceil(sqrt(pow(radius_x, 2) + pow(radius_y, 2)))) + (3 * tile_size);

		inaccessible_segment_centers_x.push_back(center_x);
		inaccessible_segment_centers_y.push_back(center_y);
		inaccessible_segment_radii.push_back(radius);
		inaccessible_tile_types.push_back(tile_type);

		num_inaccessible_segments++;
	}
}

/****************************************************************************************************/
void Map::CreateCircle(int level[num_chunks_h * num_tiles_screenHeight][num_chunks_w * num_tiles_screenWidth], double map_frac_start_w, double map_frac_start_h, double rad, bool accessible, int tile_type)
{
	int center_x_tile = int(num_tiles_screenWidth * num_chunks_w * map_frac_start_w) + int(rad);
	int center_y_tile = int(num_tiles_screenHeight * num_chunks_h * map_frac_start_h) + int(rad);

	for (int i = int(num_tiles_screenWidth * num_chunks_w * map_frac_start_w); i < int(num_tiles_screenWidth * num_chunks_w * map_frac_start_w) + int(2 * rad); i++)
	{
		for (int j = int(num_tiles_screenHeight * num_chunks_h * map_frac_start_h); j < int(num_tiles_screenHeight * num_chunks_h * map_frac_start_h) + int(2 * rad); j++)
		{
			if (pow(i - center_x_tile, 2) + pow(j - center_y_tile, 2) < pow(rad, 2))
			{
				level[j][i] = tile_type;
				if (!accessible)
				{
					// Only outermost tiles contribute to inaccessible_tiles (within radius and radius - 1)
					if (pow(i - center_x_tile, 2) + pow(j - center_y_tile, 2) >= pow(rad - 1, 2))
					{
						inaccessible_tiles[j][i] = num_inaccessible_segments + 1;
					}
				}
			}
		}
	}
	if (!accessible)
	{
		num_inaccessible_segments++;

		inaccessible_segment_centers_x.push_back((center_x_tile * tile_size) + map_x);
		inaccessible_segment_centers_y.push_back((center_y_tile * tile_size) + map_y);

		// Making radius of circle in which inaccessible area code runs be 3 more tile_sizes than the actual radius.
		int radius = (rad + 3) * tile_size;
		inaccessible_segment_radii.push_back(radius);
		inaccessible_tile_types.push_back(tile_type);
	}
}

/****************************************************************************************************/
void Map::LoadMap(int arr[num_chunks_h * num_tiles_screenHeight][num_chunks_w * num_tiles_screenWidth]) // Only called once
{
	for (int row = 0; row < num_chunks_h * num_tiles_screenHeight; row++)
	{
		for (int column = 0; column < num_chunks_w * num_tiles_screenWidth; column++)
		{
			map[row][column] = arr[row][column];
		}
	}
}

/****************************************************************************************************/
void Map::GetCurrentTileType()
{
	
}

/****************************************************************************************************/
void Map::GetInaccessibleTileCoords() // Only called once. Goes through the map num_inaccessible_segments times to get an x and y vector of each segment's coordinates.
{
	// The inaccessible segment coordinates change based on the player's movement, just like the background does.
	// Need to update the position of the inaccessible segment coordinates when player moves (this is done in Character -> Update).

	for (int i = 1; i <= num_inaccessible_segments; i++)
	{
		std::vector<int> inaccessible_segment_x;
		std::vector<int> inaccessible_segment_y;

		for (int row = 0; row < num_chunks_h * num_tiles_screenHeight; row++)
		{
			for (int column = 0; column < num_chunks_w * num_tiles_screenWidth; column++)
			{
				if (inaccessible_tiles[row][column] == i)
				{
					inaccessible_segment_x.push_back((column * tile_size) + map_x);
					inaccessible_segment_y.push_back((row * tile_size) + map_y);
				}
			}
		}
		inaccessible_segments_x.push_back(inaccessible_segment_x);
		inaccessible_segments_y.push_back(inaccessible_segment_y);
	}
}

/****************************************************************************************************/
void Map::GetCurrentChunk()
{
	// Chunk numbering arranged from top left (1) read like a sentence, from left to right and top to bottom, ending at bottom right.
	int chunk = 1;
	bool break_loop = false;
	for (int i = num_chunks_h / 2; i >= -((num_chunks_h / 2) - 1); i--)
	{
		for (int j = num_chunks_w / 2; j >= -((num_chunks_w / 2) - 1); j--)
		{
			if ((map_x <= map_x_start + (Game::screenWidth / 2) + (j * Game::screenWidth)) & (map_x >= map_x_start - (Game::screenWidth / 2) + (j * Game::screenWidth)) & (map_y <= map_y_start + (Game::screenHeight / 2) + (i * Game::screenHeight)) & (map_y >= map_y_start - (Game::screenHeight / 2) + (i * Game::screenHeight)))
			{
				current_chunk = chunk;
				break_loop = true;
				break;
			}
			chunk += 1;
		}
		if (break_loop)
		{
			break;
		}
	}
}

/****************************************************************************************************/
void Map::GetNeighborChunks() // Only draw the chunks nearest to player - top, bottom, left, right and diagonals (8 max)
{
	// neighbor_chunks vector contains chunk number of all neighbor chunks, including current chunk
	neighbor_chunks.push_back(current_chunk);

	if (current_chunk - num_chunks_w > 0) // Has a top neighbor
	{
		neighbor_chunks.push_back(current_chunk - num_chunks_w);
	}
	if (current_chunk <= num_chunks_w * (num_chunks_h - 1)) // Has a bottom neighbor
	{
		neighbor_chunks.push_back(current_chunk + num_chunks_w);
	}
	if (current_chunk % num_chunks_w != 0) // Has a right neighbor
	{
		neighbor_chunks.push_back(current_chunk + 1);
	}
	if (current_chunk % num_chunks_w != 1) // Has a left neighbor
	{
		neighbor_chunks.push_back(current_chunk - 1);
	}
	if ((current_chunk % num_chunks_w != 1) & (current_chunk - num_chunks_w > 0)) // Has a top left neighbor
	{
		neighbor_chunks.push_back(current_chunk - num_chunks_w - 1);
	}
	if ((current_chunk % num_chunks_w != 1) & (current_chunk <= num_chunks_w * (num_chunks_h - 1))) // Has a bottom left neighbor
	{
		neighbor_chunks.push_back(current_chunk + num_chunks_w - 1);
	}
	if ((current_chunk - num_chunks_w > 0)& (current_chunk % num_chunks_w != 0)) // Has a top right neighbor
	{
		neighbor_chunks.push_back(current_chunk - num_chunks_w + 1);
	}
	if ((current_chunk <= num_chunks_w * (num_chunks_h - 1)) & (current_chunk % num_chunks_w != 0)) // Has a bottom right neighbor
	{
		neighbor_chunks.push_back(current_chunk + num_chunks_w + 1);
	}
}

/****************************************************************************************************/
void Map::DrawNeighborChunks() // Called every game loop
{
	// Draws the current chunk the player is in and all neighboring chunks. Increases performance because the whole map doesn't have to constantly update!
	GetCurrentChunk();
	GetNeighborChunks();
	int chunk_col; int chunk_row; int type;

	for (auto i = neighbor_chunks.begin(); i != neighbor_chunks.end(); ++i) // use *i when referring to elements
	{
		if (*i % num_chunks_w == 0)
		{
			chunk_col = num_chunks_w;
			chunk_row = *i/ num_chunks_w;
		}
		else
		{
			chunk_col = *i % num_chunks_w;
			chunk_row = (*i / num_chunks_w) + 1; // integer division + 1
		}

		for (int row = (chunk_row - 1) * num_tiles_screenHeight; row < chunk_row * num_tiles_screenHeight; row++)
		{
			for (int col = (chunk_col - 1) * num_tiles_screenWidth; col < chunk_col * num_tiles_screenWidth; col++)
			{
				type = map[row][col];
				dest.x = (col * tile_size) + map_x;
				dest.y = (row * tile_size) + map_y;

				switch (type)
				{
				case 0:
					TextureManager::Draw(dirt, src, dest);
					break;
				case 1:
					TextureManager::Draw(grass, src, dest);
					break;
				case 2:
					TextureManager::Draw(water, src, dest);
					break;
				default:
					break;
				}
			}
		}
	}

	neighbor_chunks.clear();
}

/****************************************************************************************************/
void Map::DrawFullMap() // Called every game loop
{
	int type = 0;

	for (int row = 0; row < num_chunks_h * num_tiles_screenHeight; row++)
	{
		for (int column = 0; column < num_chunks_w * num_tiles_screenWidth; column++)
		{
			type = map[row][column];

			dest.x = (column * tile_size) + map_x; // Starting from top left of total map (assume even number of chunks).
			dest.y = (row * tile_size) + map_y;

			switch (type)
			{
			case 0:
				TextureManager::Draw(dirt, src, dest);
				break;
			case 1:
				TextureManager::Draw(grass, src, dest);
				break;
			case 2:
				TextureManager::Draw(water, src, dest);
				break;
			default:
				break;
			}
		}
	}
}

/****************************************************************************************************/
std::vector<Map*> Map::getAllObjects()
{
	return objList;
}

/****************************************************************************************************/
void Map::ClearDrawVectors()
{
	inaccessible_segments_x.clear();
	inaccessible_segments_y.clear();

	inaccessible_segment_centers_x.clear();
	inaccessible_segment_centers_y.clear();
	inaccessible_segment_radii.clear();
	inaccessible_tile_types.clear();
}

/****************************************************************************************************/