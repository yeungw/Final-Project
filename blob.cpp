#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <ctime>

typedef SDL_Texture* Texture;

unsigned window_x = 800;
unsigned window_y = 600;

unsigned window_start_x = 200;
unsigned window_start_y = 100;

double vertical = 0.5;
double horizontal = 0.5;

double player_speed = 0.01;

int player_down = 0;
int player_right = 0;
int player_up = 0;
int player_left = 0;

double scale_factor = 1;

SDL_Renderer *renderer;

int main( int argc, char* argv[] ){
   if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
      printf("SDL_Init failed: %s\n", SDL_GetError());
      return 1;
   }

   SDL_Window *window = SDL_CreateWindow("My game",window_start_x,window_start_y, window_x,window_y,SDL_WINDOW_SHOWN);
   if (!window){
      printf("Window creation failed: %s\n", SDL_GetError());
      SDL_Quit();
      return 1;
   }

   renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
   if (!renderer){
      printf("Renderer creation failed: %s\n", SDL_GetError());
      SDL_Quit();
      return 1;
   }

   if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ) {
        printf("Audio creation failed %s\n", Mix_GetError());
        return 1;
   }

   Mix_Chunk *fail = Mix_LoadWAV("fail.wav");
   if(!fail){
        printf("Could not open sound effect %s\n", Mix_GetError());
   }

   Mix_Chunk *ding = Mix_LoadWAV("Ding.wav");
   if(!ding){
        printf("Could not open sound effect %s\n", Mix_GetError());
   }

   //Our event structure
   SDL_Event e;
   int quit = 0;
   while (!quit){
      while (SDL_PollEvent(&e)){
         if (e.type == SDL_QUIT) quit = 1;
         else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
            switch(e.key.keysym.sym){
               case SDLK_LEFT:
                  player_left = (e.type == SDL_KEYDOWN); break;
               case SDLK_RIGHT:
                  player_right = (e.type == SDL_KEYDOWN); break;
               case SDLK_UP:
                  player_up = (e.type == SDL_KEYDOWN); break;
               case SDLK_DOWN:
                  player_down = (e.type == SDL_KEYDOWN); break;
            }
         }
      }

      vertical+= (player_down - player_up) * player_speed;
      if(vertical > (1.0-.025)) vertical = 1.0-.025 ;
      else if(vertical < 0) vertical = 0;

      horizontal+= (player_right - player_left) * player_speed;
      if(horizontal > 1.0-.025) horizontal = 1.0-.025;
      else if(horizontal < 0) horizontal = 0;


      SDL_RenderClear(renderer);

      //SDL_SetRenderDrawColor(renderer,255,255,255,255);
      SDL_SetRenderDrawColor(renderer,0,0,0,0); //background
      SDL_Rect rectangle;
      rectangle.x = 0;
      rectangle.y = 0;
      rectangle.w = window_x;
      rectangle.h = window_y;
      SDL_RenderFillRect(renderer, &rectangle);

      SDL_SetRenderDrawColor(renderer,255,255,255,255); //moving block
      SDL_Rect block;
      block.x = horizontal*rectangle.w;
      block.y = vertical*rectangle.h;
      block.w = 10*scale_factor;
      block.h = 10*scale_factor;
      SDL_RenderFillRect(renderer, &block);

      int x;
      srand(time(NULL));
      x = rand()%15;
      SDL_SetRenderDrawColor(renderer,0,0,255,255);
      SDL_Rect reward_1;
      if (x==5  || x==12) {
          reward_1.x = rand()%window_x;
          reward_1.y = rand()%window_y;
          reward_1.w = 25;
          reward_1.h = 25;
      }
      if (abs(reward_1.x-block.x)<((block.w/2+reward_1.w/2)) && abs(reward_1.y-block.y)<((block.h/2+reward_1.h/2))) {
          Mix_PlayChannel( -1, ding, 0 );
          if (scale_factor < 30) {
              scale_factor += .5;
          } else {
              scale_factor = scale_factor;
          }
          reward_1.x = rand()%window_x;
          reward_1.y = rand()%window_y;
      }
      SDL_RenderFillRect(renderer, &reward_1);

      SDL_SetRenderDrawColor(renderer,255,0,0,255);
      SDL_Rect obstacle_1;
      if (x==9) {
          obstacle_1.x = rand()%window_x;
          obstacle_1.y = rand()%window_y;
          obstacle_1.w = 25;
          obstacle_1.h = 25;
      }
      if ((abs(obstacle_1.x-block.x)<((block.w/2+obstacle_1.w/2))) && (abs(obstacle_1.y-block.y)<((obstacle_1.h/2+block.h/2)))) {
          Mix_PlayChannel( -1, fail, 0 );
          scale_factor -= 1;
          obstacle_1.x = rand()%window_x;
          obstacle_1.y = rand()%window_y;

      }
      SDL_RenderFillRect(renderer, &obstacle_1);

      SDL_Rect obstacle_2;
      if (x==2) {
          obstacle_2.x = rand()%window_x;
          obstacle_2.y = rand()%window_y;
          obstacle_2.w = 25;
          obstacle_2.h = 25;
      }
      if ((abs(obstacle_2.x-block.x)<((block.w/2+obstacle_2.w/2))) && (abs(obstacle_2.y-block.y)<((obstacle_2.h/2+block.h/2)))) {
          Mix_PlayChannel( -1, fail, 0 );
          scale_factor -= 1;
          obstacle_2.x = rand()%window_x;
          obstacle_2.y = rand()%window_y;
      }
      SDL_RenderFillRect(renderer, &obstacle_2);

      SDL_Rect obstacle_3;
      if (x==7) {
          obstacle_3.x = rand()%window_x;
          obstacle_3.y = rand()%window_y;
          obstacle_3.w = 25;
          obstacle_3.h = 25;
      }
      if ((abs(obstacle_3.x-block.x)<((block.w/2+obstacle_3.w/2))) && (abs(obstacle_3.y-block.y)<((obstacle_3.h/2+block.h/2)))) {
          Mix_PlayChannel( -1, fail, 0 );
          scale_factor -= 1;
          obstacle_3.x = rand()%window_x;
          obstacle_3.y = rand()%window_y;
      }
      SDL_RenderFillRect(renderer, &obstacle_3);

      SDL_RenderPresent(renderer);

      if (scale_factor <= 0) {
          return 0;
      }
   }

   return 0;
}
