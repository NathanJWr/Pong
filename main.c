#include "display.h"
#include "structs.h"
#include "move.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_W 600
#define SCREEN_H 400

#define PADDLE_W (SCREEN_W / 25)
#define PADDLE_H (SCREEN_H / 3)
int main() {
  const int gameTick = 128;
  const int waittime = 1000.0f/gameTick;
  int next_game_step = SDL_GetTicks(); //initial value
 
    const int renderFPS = 1000.0f/60;
    int framestarttime = 0;
  //Create Game Objects
  SDL_Rect paddle1 = 
  {10, (SCREEN_H / 2) - (PADDLE_H / 2), PADDLE_W, PADDLE_H}; 
 
  SDL_Rect paddle2 =
  {SCREEN_W - PADDLE_W - 10,
    (SCREEN_H / 2) - (PADDLE_H / 2), PADDLE_W, PADDLE_H};

  srand(time(0));
  int dy = (rand() % 4) - 2;
  Ball ball = {SCREEN_W / 2, SCREEN_H / 2, 10, 2, dy};



  initVideo();
  bool quit = false;
  SDL_Event e;

  //Game Loop
  while(!quit) {
    int now = SDL_GetTicks();
    //Game logic
    if(next_game_step <= now) {
      int limit = 10;
      while((next_game_step <= now) && (limit--)) {
        moveAIPaddle(&paddle2, &ball);
        moveBall(&ball, &paddle1, &paddle2);
        while(SDL_PollEvent(&e) != 0) {
          if(e.type == SDL_QUIT) {
          quit = true;
        }
          else {
            movePaddle(&e, &paddle1);
          }
        }
        next_game_step += waittime;
      }
      //Rendering
      drawPaddle(&paddle2);
      drawPaddle(&paddle1);
      drawBall(&ball);
      updateScreen();
    }
    //limit fps
    int delaytime = renderFPS - (SDL_GetTicks() - framestarttime);
    if(delaytime > 0) {
      SDL_Delay(delaytime);
    }
    framestarttime = SDL_GetTicks();
  }
  killDisplay();
  return 0;
}
