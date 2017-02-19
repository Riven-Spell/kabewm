#include <common.h>
#include "spritesheets/assets.c"

// The following assumes a 128x128px spritesheet with 16x16px sprites.
#define render_sprite(spritesheet, sprite_index, x, y) ST_RenderSpritePosition((spritesheet), ((sprite_index) % 8) * 16, ((sprite_index) / 8) * 16, 16, 16, (x), (y)) 

//extern const st_image player_spritesheet;

int main(int argc, char **argv) {
	ST_Init();

	int framecount = 0;

	st_spritesheet *player_ss = ST_SpritesheetCreateSpritesheet(
		main_spritesheet_data.pixel_data,
		main_spritesheet_data.width,
		main_spritesheet_data.height);

	while(aptMainLoop())
	{
		ST_RenderStartFrame(GFX_TOP);
		ST_InputScan();

		/*ST_RenderSpritePosition(
			player_ss,
			0, 0,
			16, 16,
			100, 100
		);*/

		int index;
		if(framecount % 4 == 0)
			index = 4;
		else if(framecount % 4 == 2)
			index = 5;
		else
			index = 3;

		render_sprite(player_ss, index, 100, 100); 

		ST_RenderEndRender();
		framecount++;
	}

	ST_SpritesheetFreeSpritesheet(player_ss);
	ST_Fini();
	return 0;
}
