// header files included
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

// screen dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


// global variables (dont do this in bigger projects)
SDL_Window* gWindow = NULL; // the SDL window 

SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;

bool quit = false; // event variable to tell the window to close
SDL_Event e; // event handler object (used to track key presses, mouse motion, joy buttons, etc.)

bool init() {  // function to open SDL window
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false; // error in SDL 
    }
    else {
        // create the SDL window
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        else {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL) {
                printf("Renderer could not be initialized! SDL Error: %s\n", SDL_GetError());
                return false;
            }
            else {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF); // set color of renderer

                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) && imgFlags)) {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    return false;
                }
            }
        }
    }
    return true;
}

SDL_Texture* loadTexture(std::string path) {
    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf("Error loading BMP image: %s, %s\n", path.c_str(), IMG_GetError());
    }
    else {
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL) {
            printf("Error loading BMP image: %s, %s\n", path.c_str(), SDL_GetError());
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

bool loadMedia() {
    return true;
}

void close() {
    SDL_DestroyWindow(gWindow); // destroy window
    SDL_DestroyTexture(gTexture);
    SDL_DestroyRenderer(gRenderer);
    gWindow = NULL;
    gTexture = NULL;
    gRenderer = NULL;

    IMG_Quit();
    SDL_Quit(); // quit subsystems
}

int main(int argc, char* args[]) {
    // open SDL window using above defined function
    if(!init()) {
        printf("Failed to initialize!\n");
    }
    else {
        if (!loadMedia()) {
            printf("Media failed to load!\n");
        }
        else {
            SDL_Event e; 

            while(!quit){ 
                while(SDL_PollEvent(&e)){ 
                    if( e.type == SDL_QUIT ) 
                        quit = true; 
                }
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );

                // Render a rectangle
                SDL_Rect fillRect = {SCREEN_WIDTH/4, SCREEN_HEIGHT/4, SCREEN_WIDTH/2, SCREEN_HEIGHT/2};
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
                SDL_RenderFillRect(gRenderer, &fillRect);

                // render rect outline

                SDL_Rect outlineRect = {SCREEN_WIDTH/6, SCREEN_HEIGHT/6, SCREEN_WIDTH * 2/3, SCREEN_HEIGHT * 2/3};
                SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );
                SDL_RenderDrawRect(gRenderer, &outlineRect);

                SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF );
                SDL_RenderDrawLine( gRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 );

                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0x00, 0xFF );
                for( int i = 0; i < SCREEN_HEIGHT; i += 4 )
                {
                    SDL_RenderDrawPoint( gRenderer, SCREEN_WIDTH / 2, i );
                }

                //Update screen
                SDL_RenderPresent( gRenderer );
            }
        }
    }

    // destroy window & quit subsystems
    close();

    return EXIT_SUCCESS;
}