#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>

#include <stdbool.h>

int main(int argc, char* argv[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* imageTexture = NULL;
    TTF_Font* font = NULL;
    SDL_Surface* textSurface = NULL;
    SDL_Texture* textTexture = NULL;
    Mix_Music* music = NULL;

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

    // Initialisation de SDL_ttf
    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return -1;
    }

    // Initialisation de SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return -1;
    }

    window = SDL_CreateWindow("SDL Extensions Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Chargement de l'image
    imageTexture = IMG_LoadTexture(renderer, "./assets/image/texture.jpg");
    if (!imageTexture) {
        printf("Unable to load image! SDL_image Error: %s\n", IMG_GetError());
    }

    // Chargement de la police et affichage du texte
    font = TTF_OpenFont("./assets/font/Ancient Medium.ttf", 28);
    SDL_Color textColor = { 255, 255, 255 }; // Blanc
    textSurface = TTF_RenderText_Solid(font, "Test SDL_ttf!", textColor);
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    // Chargement et lecture de la musique
    music = Mix_LoadMUS("./assets/audio/animal.wav");
    if (!music) {
        printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
    }
    else {
        Mix_PlayMusic(music, -1);
    }

    // Boucle principale
    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, imageTexture, NULL, NULL); // Affiche l'image

        // Affiche le texte
        int textWidth = 0;
        int textHeight = 0;
        TTF_SizeText(font, "Test SDL_ttf!", &textWidth, &textHeight);
        SDL_Rect renderQuad = { 10, 10, textWidth, textHeight };
        SDL_RenderCopy(renderer, textTexture, NULL, &renderQuad);

        SDL_RenderPresent(renderer);
    }

    // Nettoyage
    SDL_DestroyTexture(imageTexture);
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
    Mix_FreeMusic(music);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();

    return 0;
}
