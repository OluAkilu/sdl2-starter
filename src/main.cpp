// header files included
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

// screen dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

enum KeyPressSurfaces { // this handles keypressing
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_SKEY,
    KEY_PRESS_SURFACE_TOTAL,
};

// global variables (dont do this in bigger projects)
SDL_Window* gWindow = NULL; // the SDL window 
SDL_Surface* loadSurface(std::string path); // image that we will load and show on the screen
SDL_Surface* gScreenSurface = NULL; // the surface contained in the window
SDL_Surface* gCurrentSurface = NULL; //currently displayed image
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL]; // images that correspond to a keypress (its an array of surface pointers)
SDL_Surface* gPNGSurface = NULL;
SDL_Rect stretchRect;

bool quit = false; // event variable to tell the window to close
SDL_Event e; // event handler object (used to track key presses, mouse motion, joy buttons, etc.)

SDL_Surface* loadSurface(std::string path) {
    SDL_Surface* optimizedSurface = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf("Error loading BMP image: %s, %s\n", path.c_str(), IMG_GetError());
    }
    else {
        optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
        if (optimizedSurface == NULL) {
            printf("Error loading BMP image: %s, %s\n", path.c_str(), SDL_GetError());
        }
        SDL_FreeSurface(loadedSurface);
    }
    return optimizedSurface;
}

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
            int imgFlags = IMG_INIT_PNG; // initialize png loading
            if (!(IMG_Init(imgFlags) & imgFlags)) {
                printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                return false;
            }
            else {
                gScreenSurface = SDL_GetWindowSurface(gWindow); // gets window surface
            }
        }
    }
    return true;
}

bool loadMedia() {
    gPNGSurface = loadSurface("src/loaded.png");
    if (gPNGSurface == NULL) {
		printf( "Failed to load PNG image!\n" );
		return false;
	}
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = gPNGSurface;
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
        printf("Error loading png image!");
        return false;
    }

    gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = SDL_LoadBMP("src/up.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL) {
        printf("Error loading BMP image: %s\n", SDL_GetError());
        return false;
    }

    gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = SDL_LoadBMP("src/down.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL) {
        printf("Error loading BMP image: %s\n", SDL_GetError());
        return false;
    }

    gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = SDL_LoadBMP("src/left.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL) {
        printf("Error loading BMP image: %s\n", SDL_GetError());
        return false;
    }

    gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = SDL_LoadBMP("src/right.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL) {
        printf("Error loading BMP image: %s\n", SDL_GetError());
        return false;
    }

    gKeyPressSurfaces[KEY_PRESS_SURFACE_SKEY] = SDL_LoadBMP("src/stretch.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_SKEY] == NULL) {
        printf("Error loading BMP image: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

void close() {
    for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++) {
        SDL_FreeSurface(gKeyPressSurfaces[i]);
        gKeyPressSurfaces[i] = NULL; // good practice maybe
    }

    SDL_DestroyWindow(gWindow); // destroy window
    gWindow = NULL;
    gPNGSurface = NULL;

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
            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

            while(!quit){ 
                while(SDL_PollEvent(&e)){ 
                    if( e.type == SDL_QUIT ) 
                        quit = true; 
                    else if (e.type == SDL_KEYDOWN) {
                        switch (e.key.keysym.sym) {
                            case SDLK_UP:
                                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
                                break;
                            case SDLK_DOWN:
                                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                                break;
                            case SDLK_LEFT:
                                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
                                break;
                            case SDLK_RIGHT:
                                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
                                break;
                            case SDLK_s:
                                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_SKEY];
                                stretchRect.x = 0;
                                stretchRect.y = 0;
                                stretchRect.w = SCREEN_WIDTH;
                                stretchRect.h = SCREEN_HEIGHT;
                                break;
                            case SDLK_q:
                                quit = true;
                                break;
                            default:
                                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
                                break;
                        }
                    }
                }
                if (gCurrentSurface == gKeyPressSurfaces[KEY_PRESS_SURFACE_SKEY]) {
                    SDL_BlitScaled(gCurrentSurface, NULL, gScreenSurface, &stretchRect);
                    SDL_UpdateWindowSurface( gWindow ); // update screen
                }
                else {
                SDL_BlitSurface( gCurrentSurface, NULL, gScreenSurface, NULL ); // apply image to screen
                SDL_UpdateWindowSurface( gWindow ); // update screen
                }
            }
        }
    }

    // destroy window & quit subsystems
    close();

    return EXIT_SUCCESS;
}