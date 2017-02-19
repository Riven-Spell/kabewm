#pragma once

#define WORLD_HEIGHT 15
#define WORLD_WIDTH  15

#include "entity.h"
#include "player.h"
#include "common.h"
#include "levels.h"
class World
{
	public:
		Entity grid[WORLD_HEIGHT][WORLD_WIDTH];
		Player player;
		struct { int x, y; } end_position;	
		bool player_won();
		u64 start_time;
		World(st_spritesheet *sheet);
		void clear(st_spritesheet *sheet);
		void render_all(bool isPlayer, int framecount);
		void add_to_grid(int x, int y, Entity ent);
		bool assert_valid_spot(int x, int y);
		bool player_can_move_rel(int dx, int dy);
		void clear_spot(st_spritesheet *sheet, int x, int y);
		bool player_is_on_mine();
		void load_level(st_spritesheet* sheet, level_t level);
};
