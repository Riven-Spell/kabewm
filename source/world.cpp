#include "world.h"

bool World::player_can_move_rel(int dx, int dy)
{
	return (assert_valid_spot(this->player.position.x + dx, this->player.position.y + dy) &&\
					(this->grid[this->player.position.y + dy][this->player.position.x + dx].collision != COLLISION_WALL));
}

World::World(st_spritesheet *sheet)
{
	std::vector<unsigned char> frames = {PLAYER_UP_STAND, PLAYER_RIGHT_STAND, PLAYER_LEFT_STAND, PLAYER_DOWN_STAND};
	this->clear(sheet);
	this->player = Player(sheet, frames);
}

void World::clear(st_spritesheet *sheet)
{
	std::vector<unsigned char> blank = {63};
	for(int i=0; i<WORLD_HEIGHT; i++)
		for(int j=0; j<WORLD_WIDTH; j++)
			grid[i][j] = Entity(sheet, blank, COLLISION_NONE);
}

void World::render_all(bool isPlayer, int framecount)
{
	for(int i=0; i<WORLD_HEIGHT; i++){
		for(int j=0; j<WORLD_WIDTH; j++){
			Entity ent = grid[i][j];
			int col = ent.collision;
			//if(grid[i][j].frames.size() && ((isPlayer && grid[i][j].collision != COLLISION_MINE_SPECTATOR) || (!isPlayer && grid[i][j].collision != COLLISION_MINE_PLAYER)))
			if((isPlayer && col != COLLISION_MINE_SPECTATOR) || (!isPlayer && col != COLLISION_MINE_PLAYER && col != COLLISION_WALL))
				grid[i][j].render_next_frame(framecount);
		}
	}
	this->player.render_next_frame(1);
}

void World::add_to_grid(int x, int y, Entity ent)
{
	assert_valid_spot(x,y);
	ent.position = {x, y};
	grid[y][x] = ent;
}

void World::clear_spot(st_spritesheet *sheet, int x, int y)
{
	std::vector<unsigned char> blank = {63};
	assert_valid_spot(x, y);
	grid[y][x] = Entity(sheet, blank, COLLISION_NONE);
}

bool World::assert_valid_spot(int x, int y)
{
	return ((0 <= x) && (x < WORLD_WIDTH) &&
	     		(0 <= y) && (y < WORLD_HEIGHT));
}

bool World::player_is_on_mine()
{
	return this->grid[this->player.position.y][this->player.position.x].collision & (COLLISION_MINE_SPECTATOR | COLLISION_MINE_PLAYER);
}

void World::load_level(st_spritesheet *sheet, level_t level)
{
	Entity ent;
	for (int i = 0; i < WORLD_HEIGHT; i++)
		for (int j = 0; j < WORLD_WIDTH; j++)
		{
			switch (level.map[i][j])
			{
				case B:
					ent = Entity(sheet, {63}, COLLISION_NONE);
					break;
				case W:
					ent = Entity(sheet, {WALL}, COLLISION_WALL);
					break;
				case P:
					ent = Entity(sheet, {WATER_1, WATER_2, WATER_3, WATER_4}, COLLISION_WALL);
					break;
				case S:
					ent = Entity(sheet, {MINE_OFF, MINE_ON}, COLLISION_MINE_SPECTATOR);
					break;
				case M:
					ent = Entity(sheet, {MINE_OFF, MINE_ON}, COLLISION_MINE_PLAYER);
					break;
				case D:
					ent = Entity(sheet, {MINE_OFF, MINE_OFF, MINE_ON, MINE_OFF, MINE_ON, MINE_OFF}, COLLISION_DUD);
					break;
				case R:
					ent = Entity(sheet, {ROCK}, COLLISION_NONE);
					break;
				default:
					ent = Entity(sheet, {63}, COLLISION_NONE);
			}
			ent.position = {j, i};
			grid[i][j] = ent;
		}
	this->player.position.x = level.start_position.x;
	this->player.position.y = level.start_position.y;
	this->end_position.x = level.end_position.x;
	this->end_position.y = level.end_position.y;
	this->start_time = ST_TimeRunning();
}

bool World::player_won()
{
	return this->player.position.x == this->end_position.x &&\
				 this->player.position.y == this->end_position.y;
}

/*
World::move_player(int direction)
{
	switch(direction){
	case DIR_UP:
		move_player(0,-1);
		break;
	case DIR_DOWN:
		move_player(0,1);
		break;
	case DIR_LEFT:
		move_player(-1,0);
		break;
	case DIR_RIGHT:
		move_player(1,0);
		break
	}
*/
