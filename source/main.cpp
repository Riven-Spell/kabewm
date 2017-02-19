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
	30,
	{ {W, W, W, W, W, W, W, W, W, W, W, W, W, W, W},
		{W, B, B, B, B, B, B, B, B, B, B, B, B, R, W},
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
int main(int argc, char **argv) {
	ST_Init();
	consoleInit(GFX_BOTTOM, NULL);
	int framecount = 0;
	u64 game_clock;
	st_spritesheet *player_ss = ST_SpritesheetCreateSpritesheet(
		main_spritesheet_data.pixel_data,
		main_spritesheet_data.width,
		main_spritesheet_data.height);
	ST_RenderSetBackground(0x82, 0xE1, 0x11);
	World world = World(player_ss);
	world.load_level(player_ss, level1);
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
			world.render_all(true, framecount);
			game_clock = ST_TimeRunning() - world.start_time;
			if (game_clock > 1000 * level1.seconds)
				world.load_level(player_ss, level1);
			else
				printf("\x1b[0;0H%03d",level1.seconds - (int)game_clock/1000);	
		ST_RenderEndRender();
		if (world.player_won())
			world.load_level(player_ss, level1);
		if (world.player_is_on_mine())
			world.load_level(player_ss, level1);
		framecount++;
	}

	ST_SpritesheetFreeSpritesheet(player_ss);
	ST_Fini();
	return 0;
}
