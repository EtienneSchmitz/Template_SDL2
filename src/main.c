#include <SDL.h>

int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	SDL_Quit();

	return 0;
}