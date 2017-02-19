#include <common.h>
#include "spritesheets/assets.c"
#include "entity.h"
#include "player.h"
#include "world.h"
#include "levels.h"
// The following assumes a 128x128px spritesheet with 16x16px sprites.
#define render_sprite(spritesheet, sprite_index, x, y) ST_RenderSpritePosition((spritesheet), ((sprite_index) % 8) * 16, ((sprite_index) / 8) * 16, 16, 16, (x), (y)) 

//extern const st_image player_spritesheet;
level_t level1 =\
{
  {1, 13},
  {13, 1},
  120,
  { {W, W, W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, B, B, B, B, B, B, B, B, B, W},
    {W, B, B, B, B, B, B, B, B, B, B, B, B, B, W},
    {W, B, B, B, B, B, B, B, B, B, B, B, B, B, W},
    {W, B, B, B, B, B, B, B, B, B, B, B, B, B, W},
    {W, B, B, B, B, B, B, B, B, B, B, B, B, B, W},
    {W, B, B, B, W, B, B, B, B, B, B, B, B, B, W},
    {W, B, B, S, B, S, B, B, B, B, B, B, B, B, W},
    {W, W, W, W, B, B, B, B, B, B, B, B, B, B, W},
    {W, B, B, W, B, W, M, M, B, W, B, B, B, B, W},
    {W, D, B, B, B, S, S, S, B, W, B, B, B, B, W},
    {W, B, P, P, W, M, M, M, M, W, B, B, B, B, W},
    {W, B, P, P, B, B, B, W, W, W, B, B, B, B, W},
    {W, B, B, S, P, B, B, B, B, B, B, B, B, B, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W, W, W} }
};

level_t level2 =\
{
  {1, 1 },
  {13, 10},
  20, //Is this even possible? I have no idea.
  //                               1  1  1  1  1
  // 0  1  2  3  4  5  6  7  8  9  0  1  2  3  4
  { {W, W, W, W, W, W, W, W, W, W, W, W, W, W, W}, //0
    {W, B, W, B, B, B, B, B, W, B, B, B, S, B, W}, //1
    {W, B, S, B, S, B, S, B, B, S, B, B, W, B, W}, //2
    {W, B, S, B, S, B, S, B, B, S, B, B, S, B, W}, //3
    {W, B, B, B, W, B, W, B, B, B, B, B, S, B, W}, //4
    {W, S, S, S, S, S, S, S, S, S, B, B, B, B, W}, //5
    {W, B, B, B, S, B, B, B, B, S, S, S, S, B, W}, //6
    {W, B, S, B, S, B, S, S, B, B, S, B, B, B, W}, //7
    {W, B, S, B, S, B, B, S, S, B, S, B, S, B, W}, //8
    {W, B, S, B, S, S, B, S, B, B, S, B, S, S, W}, //9
    {W, B, D, B, B, B, B, S, B, S, S, B, S, B, W}, //10
    {W, B, S, S, S, S, S, S, B, B, B, B, S, B, W}, //11
    {W, B, S, S, S, S, S, S, S, S, S, S, S, B, W}, //12
    {W, B, B, B, B, B, B, B, B, B, B, B, B, B, W}, //13
    {W, W, W, W, W, W, W, W, W, W, W, W, W, W, W} }//14
};
	
int main(int argc, char **argv) {
	ST_Init();

	int framecount = 0;

	st_spritesheet *player_ss = ST_SpritesheetCreateSpritesheet(
		main_spritesheet_data.pixel_data,
		main_spritesheet_data.width,
		main_spritesheet_data.height);
	World world = World(player_ss);
	world.load_level(player_ss, level2);
	bool player_mode = true;
	while(aptMainLoop())
	{
		ST_RenderStartFrame(GFX_TOP);
		ST_InputScan();
			if (ST_InputButtonPressed(KEY_DUP))
			{
				if (world.player_can_move_rel(0, -1))
					world.player.move_rel(0, -1);
				world.player.direction = UP;
			}

			if (ST_InputButtonPressed(KEY_DDOWN))
			{
				if (world.player_can_move_rel(0, 1))
					world.player.move_rel(0, 1);
				world.player.direction = DOWN;
			}
			if (ST_InputButtonPressed(KEY_DLEFT))
			{
				if (world.player_can_move_rel(-1, 0))
					world.player.move_rel(-1, 0);
				world.player.direction = LEFT;
			}
			if (ST_InputButtonPressed(KEY_DRIGHT))
			{
				if (world.player_can_move_rel(1, 0))
					world.player.move_rel(1, 0);
				world.player.direction = RIGHT;
			}
			if (ST_InputButtonPressed(KEY_SELECT))
			{
				player_mode = !player_mode;
			}
			world.render_all(player_mode, framecount);
		ST_RenderEndRender();
		if (world.player_is_on_mine())
			world.load_level(player_ss, level2);
		framecount++;
	}

	ST_SpritesheetFreeSpritesheet(player_ss);
	ST_Fini();
	return 0;
}
