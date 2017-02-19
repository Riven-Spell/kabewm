#include "player.h"
Player::Player(st_spritesheet *spritesheet, std::vector<unsigned char> frames)
{
	Entity::Entity(spritesheet, frames);
}
