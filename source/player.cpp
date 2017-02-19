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

Player::Player() : Entity(NULL, std::vector<unsigned char>(), COLLISION_NONE) {} //WHAT THE FUCK
Player::Player(st_spritesheet *spritesheet, std::vector<unsigned char> frames) : Entity(spritesheet, frames, COLLISION_NONE) {}

void Player::render_next_frame(int framecount)
{
	ST_RenderSpritePosition(this->spritesheet, (int)(this->frames[this->direction] % 8) * 16, (int)(this->frames[this->direction] / 8) * 16, 16, 16, this->position.x * 16 + 80, this->position.y * 16);
}
