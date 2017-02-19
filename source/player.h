#pragma once
#include "entity.h"
#include "common.h"
#include <vector>

enum playerDirections
{
	UP = 0,
	RIGHT,
	LEFT,
	DOWN
};

class Player : public Entity
{
	public:
		int direction;
		void move_rel(int dx, int dy);

		Player();
		Player(st_spritesheet *spritesheet, std::vector<unsigned char> frames);
		void render_next_frame(int framecount) override;
};
