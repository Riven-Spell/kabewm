#pragma once
#include "entity.h"
#include "common.h"
#include <vector>

class Player : public Entity
{
	public:
		int direction;
		void move_rel(int dx, int dy);
		Player();
		Player(st_spritesheet *spritesheet, std::vector<unsigned char> frames);
};
