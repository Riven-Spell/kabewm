#pragma once
enum Entity_Type
{
	B = 0,	// Blank
	W,		 	// Wall
	P,			// Pond
	S,			// Spectator Mine
	M,			// Player Mine
	D,			// Dud Mine
	R				// Rock (ugly af)
};

struct level_t
{
	struct { int x, y; } start_position;
	struct { int x, y; } end_position;
	int seconds;
	unsigned char map[15][15];
};



