#include "player.h"

void Player::move_rel(int dx, int dy)
{
	if (this->position.x + dx < 15 &&\
			this->position.x + dx > -1 &&\
			this->position.y + dy < 15 &&\
			this->position.y + dy > -1)
	{
		this->position.x += dx;
		this->position.y += dy;
	}
}

Player::Player(st_spritesheet *spritesheet, std::vector<unsigned char> frames) : Entity(spritesheet, frames, COLLISION_NONE) {}
