#include <common.h>
#ifndef OBJECT_H
#define OBJECT_H

class Object 
{
public:
	Object(SpriteSheet s, int x, int y);
	~Object();

	virtual void Update();
	virtual void ChangeSpriteLoc(int x, int y);
	virtual void Move(int x, int y);
	virtual void Draw();
private:
	SpriteSheet s;
	int x;
	int y;
	int sx;
	int sy;
}

struct SpriteSheet 
{
	st_spritesheet* spritesheet;
	int sheight;
	int swidth;
}

class Player : Object 
{
public:
	Player(SpriteSheet s, int x, int y) : Object(s,x,y);
	void Update();
}

#endif
