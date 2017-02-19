#pragma once

#define WORLD_HEIGHT 15
#define WORLD_WIDTH  15

#include "entity.h"
#include "player.h"
#include "common.h"

class World
{
	public:
		Entity *grid[WORLD_HEIGHT][WORLD_WIDTH];
		Player player;

		World(st_spritesheet *sheet);
		void clear();
		void render_all();
		void add_to_grid(int x, int y, Entity ent);
		void assert_valid_spot(int x, int y);
		void clear_spot(int x, int y);
};
