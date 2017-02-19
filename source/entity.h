#pragma once
#include <vector>
#include "common.h"
enum COLLISION_TYPES
{
	COLLISION_NONE = 0,
	COLLISION_WALL,
	COLLISION_MINE_SPECTATOR,
	COLLISION_MINE_PLAYER,
	COLLISION_DUD
};

class Entity
{
	public:
		struct { int x, y; } position;
		unsigned static int last_used_id;
		unsigned int id;
		int current_frame;
		int collision;
		std::vector<unsigned char> frames;
		st_spritesheet *spritesheet;
		virtual void render_next_frame(int framecount);
		Entity(st_spritesheet *spritesheet, std::vector<unsigned char> frames, int collision);
};

