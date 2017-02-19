#include <common.h>

int main(int argc, char **argv) {
	int linkX = 5;
	int linkY = 5;
	int second = 0;
	ST_Init();
	while(aptMainLoop())
	{
		//all the top screen stuff now
		consoleInit(GFX_TOP, NULL);

		//all the bottom screen stuff now
		consoleInit(GFX_BOTTOM, NULL);
	}
	ST_Fini();
	return 0;
}
