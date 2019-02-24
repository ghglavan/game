#include "window.h"

int main(int argc, char *args[])
{
    SDL_Window *gWindow;
    SDL_Renderer *gRenderer;

    //Start up SDL and create window
    int ret = sdl::init(&gWindow, &gRenderer);
    if (ret < 0)
    {
        fprintf(stderr, "Failed to initialize: %d!\n", ret);
        return -1;
    }

    SDL_Texture *gTexture = sdl::load_texture("i-love-c.png", gRenderer);

    //Load media
    if (!gTexture)
    {
        fprintf(stderr, "Failed to load media!\n");
        //Destroy window
        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow);
        gWindow = NULL;
        gRenderer = NULL;

        return -1;
    }
    //Main loop flag
    bool quit = false;

    //Event handler
    SDL_Event e;

    //While application is running
    while (!quit)
    {
        //Handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
            //User requests quit
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        //Clear screen
        SDL_RenderClear(gRenderer);

        //Render texture to screen
        SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

        //Update screen
        SDL_RenderPresent(gRenderer);
    }

    //close SDL
    sdl::cleanup();

    //Free loaded image
    SDL_DestroyTexture(gTexture);
    gTexture = NULL;

    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    return 0;
}