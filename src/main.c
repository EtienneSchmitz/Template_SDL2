#include <SDL.h>
#include <string.h>
#include <stdlib.h>  

#include "defs.h"
#include "utils.h"
#include "structs.h"
#include "draw.h"
#include "input.h"

Application app;

int main(int argc, char* argv[]) {
	memset(&app, 0, sizeof(Application));

	initSDL();
	atexit(cleanup);

	while (1)
	{
		prepareScene();

		doInput();

		presentScene();

		SDL_Delay(16);
	}

	return 0;
}