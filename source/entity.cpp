#include "entity.h"

Entity::Entity(st_spritesheet *spritesheet, size_t framecount, int *frames)
{
	this.position = {0, 0};
	this.id = ++this.last_used_id;
	this.frames_len = frames_len;
	this.frames = frames;
	this.spritesheet = spritesheet;
	this.current_frame = 0;
}

Entity::render_next_frame(int framecount)
{
	this.current_frame = framecount % frames_len;
	ST_RenderSpritePosition(this.spritesheet, frames[current_frame , this.position.y, 16, 16, 
}
