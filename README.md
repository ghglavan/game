# game

## installation:
  * For Linux: `sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev`
  * For Windows: TODO
  
## compilation:
  * For Linux: `g++ input_file.cpp -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -o output_file`
  * For Windows: TODO
  
### SDL2 API:
  There are 543 functions we can use in SDL2. We are covering just a few basic ones here. You can find all the details you can go [here](https://wiki.libsdl.org/APIByCategory)
  
  ```C++
    int SDL_Init(Uint32 flags) // init SDL2 subsystems
  ```
  `flags` may be used for specific subsystem initialiation. We will use it as `SDL_INIT_EVERYTHING`.
  `SDL_Init` returns 0 on success or a negative error code on failure; call SDL_GetError() for more information. 
  
  ```C++
    void SDL_Quit(void) // cleanup
  ```
  
  ```C++
    SDL_Window* SDL_CreateWindow(const char* title, // the title of the window
                             int         x,         // the x position of the window, SDL_WINDOWPOS_CENTERED, or SDL_WINDOWPOS_UNDEFINED
                             int         y,         // the y position of the window, SDL_WINDOWPOS_CENTERED, or SDL_WINDOWPOS_UNDEFINED
                             int         w,         // the width of the window, in screen coordinates
                             int         h,         // the height of the window, in screen coordinates
                             Uint32      flags)
  ```
  `SDL_CreateWindow` will return a pointer to our new window on success, NULL on failure.
  `flags` can be 0 or one or more values from [here](https://wiki.libsdl.org/SDL_WindowFlags). Ill use only `SDL_WINDOW_SHOWN`.
  
  ```C++
    void SDL_DestroyWindow(SDL_Window* window) // destroy `window`
  ```
  
  ```C++
    SDL_Surface *IMG_Load(const char *file) // load an image from `file` (path to image)
  ```
   `SDL_Surface` will return a pointer to a surface on success, NULL on failure.
   A surface represents an image in RAM memory. Using RAM to store and manipulate images is not a good idea, not only because RAM memory is used for other things, but doing so is also slower than the alterntative. Using RAM is known as software rendering and is by orders of magnitude slower than hardware rendering using `SDL_Texture` (check `SDL_CreateTextureFromSurface`)
   
  ```C++
    void SDL_FreeSurface(SDL_Surface* surface) // free surface
  ```
  
  ```C++
     SDL_Surface* SDL_GetWindowSurface(SDL_Window* window) // get the surface of our window
  ```
  
  ```C++
    int SDL_BlitSurface(SDL_Surface*    src, // source surface
                    const SDL_Rect* srcrect, // a rectangle representing the part of the src surface we want to blit from
                    SDL_Surface*    dst,     // destination surface
                    SDL_Rect*       dstrect) // a rectangle representing the part of the dst surface we want to blit to
  ```
  `SDL_BlitSurface` returns 0 if the blit is successful or a negative error code on failure; call SDL_GetError() for more information. 
  If srcrect is NULL, the entire surface is copied. If dstrect is NULL, then the destination position (upper left corner) is (0, 0). 
  Usage:
  ```C++
    SDL_Rect srcrect;
    SDL_Rect dstrect;

    srcrect.x = 0;
    srcrect.y = 0;
    srcrect.w = 32;
    srcrect.h = 32;
    dstrect.x = 640/2;
    dstrect.y = 480/2;
    dstrect.w = 32;
    dstrect.h = 32;

    SDL_BlitSurface(src, &srcrect, dst, &dstrect);
  ```
  `SDL_BlitSurface` is used with surfaces. This is not optimal (see `SDL_RenderCopy`)
  
  ```C++
    SDL_Renderer* SDL_CreateRenderer(SDL_Window* window, // the window where rendering is displayed
                                 int         index, // the index of the rendering driver to initialize, or -1 to initialize the first one supporting the requested flags (we will use -1)
                                 Uint32      flags)
  ```
  `SDL_CreateRenderer` returns a valid rendering context or NULL if there was an error; call SDL_GetError() for more information.
  We will use -1 for `index` most of the time.
  `flags` can be 0 or more values from [here](https://wiki.libsdl.org/SDL_RendererFlags). We will use `SDL_RENDERER_ACCELERATED`.
  
  ```C++
    void SDL_DestroyRenderer(SDL_Renderer* renderer)
  ```
  
  
  ```C++
    int SDL_SetRenderDrawColor(SDL_Renderer* renderer,
                           Uint8         r,
                           Uint8         g,
                           Uint8         b,
                           Uint8         a)
  ```
  returns 0 on success or a negative error code on failure; call SDL_GetError() for more information. 
  
  
  ```C++
    int SDL_RenderClear(SDL_Renderer* renderer) // clear the current rendering target with the drawing color. 
  ```
  returns 0 on success or a negative error code on failure; call SDL_GetError() for more information. 
  
  ```C++
    int SDL_RenderCopy(SDL_Renderer*   renderer,
                   SDL_Texture*    texture,
                   const SDL_Rect* srcrect,
                   const SDL_Rect* dstrect)
  ```
  returns 0 on success or a negative error code on failure; call SDL_GetError() for more information. `SDL_RenderCopy` is the better alternative of `SDL_BlitSurface`
  
  ```C++
    void SDL_RenderPresent(SDL_Renderer* renderer) // make previous changes to `renderer` visible
  ```
   
  
### Architecture:
  A game has 3 basic parts: `Init`, `Loop`, `Creanup`. 
  * `Init` is the part of the game that is responsible for libraries initialization, window creation, loadin assets etc. 
  * `Cleanup` is the reverse of `Init`
  * `Loop` is the interesting part. You can think of it as an endless loop with 3 basic operations:
  ```C++
    while(game_running()){
      handle_event();
      update();
      draw();
    }
  ```
  The game `loop` is responsible for event handling, updating, and drawing. One step in our while represents one frame. Events are represented by user input (exit button click ,a key pressed, mouse movement, mouse click, joystick movement, etc.). There can be many events in a single frame, so we need to process all of them when we `handle_event`s. To do this using SDL2, we use a special class called `SDL_Event` and we `poll` every event:
  ```C++
    SDL_Event e; // event handler
    while( SDL_PollEvent( &e ) != 0 ) { 
      //User requests quit 
      if( e.type == SDL_QUIT ) 
      { 
        stop_game(); 
      } 
    }
  ```
  After handling events, we `update` our games objects based on user input. For example, if our user pressed the right arrow key, we increment our main characters x position by the amount of speed we set.
  The next step is to `draw` everything to the screen.
  
  
### You can find many good totorials about SDL [here](http://lazyfoo.net/tutorials/SDL/index.php)

## Your tasks:
  - [ ] Create a class _Window_ with methods for `init`, `cleanup`, `load_texture`, `is_running`, `draw`
