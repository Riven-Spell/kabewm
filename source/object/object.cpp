#include "object.h"

Object::Object(SpriteSheet s, int x, int y)
{
	this.s = s;
	this.x = x;
	this.y = y;
}

Object::~Object()
{
	delete this.x;
	delete this.y;
	delete this.s;
}

void Object::Update()
{}

void Object::Move(int x, int y)
{
	this.x += x;
	this.y += y;
}

void Object::Draw()
{
	ST_RenderSpritePosition(this.s.spritesheet,this.sx,this.sy,this.s.swidth,this.s.sheight,this.x,this.y);
}

void Object::ChangeSpriteLoc(int x, int y)
{
	this.sx = x;
	this.sy = y;
}

//Player
void Player::Update()
{
	ST_InputScan();
	if(ST_InputButtonDown(KEY_UP))
	{
		this.Move(0,1);
	}
	else if(ST_InputButtonDown(KEY_DOWN))
	{
		this.Move(0,-1);
	}
	else if(ST_InputButtonDown(KEY_LEFT))
	{
		this.Move(-1,0);
	}
	else if(ST_InputButtonDown(KEY_RIGHT))
	{
		this.Move(0,1);
	}
}
