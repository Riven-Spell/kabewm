#include "world.h"

World::World(st_spritesheet *sheet)
{
	std::vector<unsigned char> frames;
	frames.push_back((unsigned char)9);
	this->clear();
	this->player = Player(sheet, frames);
}

void World::clear()
{
	for(int i=0; i<WORLD_HEIGHT; i++)
		for(int j=0; j<WORLD_WIDTH; j++)
			grid[i][j] = NULL;
}

void World::render_all()
{
	for(int i=0; i<WORLD_HEIGHT; i++)
		for(int j=0; j<WORLD_WIDTH; j++)
			if(grid[i][j])
				grid[i][j]->render_next_frame(0);
	this->player.render_next_frame(1);
}

void World::add_to_grid(int x, int y, Entity ent)
{
	assert_valid_spot(x,y);
	if((!grid[y][x]))
	{
		grid[y][x] = &ent;
	}else{
		printf("attempted to add to grid position (%d,%d) that is already occupied", x, y);
	}
}

void World::clear_spot(int x, int y)
{
	assert_valid_spot(x, y);
	grid[y][x] = NULL;
}

void World::assert_valid_spot(int x, int y)
{
	if(!((0 <= x) && (x < WORLD_WIDTH ) &&
	     (0 <= y) && (y < WORLD_HEIGHT)))
		printf("not a valid spot in assert_valid_spot");
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
