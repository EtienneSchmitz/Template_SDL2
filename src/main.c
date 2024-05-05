#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>

#include <stdbool.h>

#define VELOCITY_X 3.0
#define VELOCITY_Y 3.0

void update_screen_velocity(SDL_Event event, float* xvel, float* yvel) {
    switch (event.type) {
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
        case SDLK_UP:
            *yvel = -1.0;
            break;
        case SDLK_DOWN:
            *yvel = 1.0;
            break;
        case SDLK_RIGHT:
            *xvel = 1.0;
            break;
        case SDLK_LEFT:
            *xvel = -1.0;
            break;
        }
        break;
    case SDL_KEYUP:
        switch (event.key.keysym.sym) {
        case SDLK_UP:
        case SDLK_DOWN:
            *yvel = 0.0;
            break;
        case SDLK_RIGHT:
        case SDLK_LEFT:
            *xvel = 0.0;
            break;
        }
        break;
    }
}


int main(int argc, char* argv[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* imageTexture = NULL;
    
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    // Initialisation de SDL_image
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return -1;
    }
  

    window = SDL_CreateWindow("SDL Rectangle TEST", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Chargement de l'image
    imageTexture = IMG_LoadTexture(renderer, "./assets/image/soldier/soldier.png");
    if (!imageTexture) {
        printf("Unable to load image! SDL_image Error: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        printf("Erreur lors du chargement de l'image: %s\n", IMG_GetError());
        return 1;
    }
   
    // Boucle principale
    SDL_Event e;
    bool quit = false;
    // Création du point
    SDL_Rect rect;
    rect.x = 0;  // Position horizontale de l'image sur l'écran
    rect.y = 0;  // Position verticale de l'image sur l'écran
    rect.w = 32;  // Largeur de l'image
    rect.h = 32;  // Hauteur de l'image
    float x = 0.0, y = 0.0, xvel = 0.0, yvel = 0.0;

    while (!quit) {

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else {
                update_screen_velocity(e, &xvel, &yvel);
            }
        }


        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        
		x += VELOCITY_X * xvel;
		y += VELOCITY_Y * yvel;
        rect.x = (int) x;
        rect.y = (int) y;
        SDL_RenderCopy(renderer, imageTexture, NULL, &rect);

        SDL_RenderPresent(renderer);       
        SDL_Delay(16);
    }

    // Nettoyage
    SDL_DestroyTexture(imageTexture);
    IMG_Quit();
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}