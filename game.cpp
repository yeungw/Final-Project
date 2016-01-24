#include <SDL2/SDL.h>
#include <stdio.h>

//screen dimension constants
const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 500;


int main( int argc, char* args[] ){
  SDL_Window* window = NULL;

  SDL_Surface* screenSurface = NULL;

  window = SDL_CreateWindow( "Snake^2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
  screenSurface = SDL_GetWindowSurface( window );

  //fill surface black
      SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );

      SDL_UpdateWindowSurface( window );

      SDL_Delay( 10000 );
    


  SDL_DestroyWindow( window );
  SDL_Quit();

  return 0;
}
