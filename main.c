#include "display.h"
#include "structs.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

#define SCREEN_W 600
#define SCREEN_H 400

#define PADDLE_W (SCREEN_W / 25)
#define PADDLE_H (SCREEN_H / 3)
void moveAIPaddle(SDL_Rect* paddle, Ball* ball) {
  int move_unit = 2;
  if(ball -> y > (paddle -> y) + (PADDLE_H / 2) 
      && paddle -> y <= SCREEN_H - PADDLE_H) {
    paddle -> y += move_unit;
  }
  else if(ball -> y < (paddle -> y) + (PADDLE_H / 2) 
      && paddle -> y >= 0) {
    paddle -> y -= move_unit;
  }
  printf("%d %d\n", paddle -> y + (PADDLE_H / 2), ball -> y);
}
void movePaddle(SDL_Event* e, SDL_Rect* paddle) {
  int move_unit = 8;
  if(e -> type == SDL_KEYDOWN) {
    switch(e -> key.keysym.sym) {
      case SDLK_UP:
        if(paddle -> y >= move_unit) {
          paddle -> y -= move_unit;
        }
        break;
      case SDLK_DOWN:
        if(paddle -> y <= SCREEN_H - PADDLE_H) {
          paddle -> y += move_unit;
        }
        break;
    }
  }
}

void moveBall(Ball* ball, SDL_Rect* paddle1) {
  if(ball -> x >= SCREEN_W ) {
    ball -> dx = - ball -> dx;
  }

  //Right Paddle Hit
  if(ball -> x <= (paddle1 -> x) + PADDLE_W + 3
      && ball -> x >= paddle1 -> x
      && ball -> y <= paddle1 -> y + PADDLE_H 
      && ball -> y >= paddle1 -> y) {

    ball -> dx = - ball -> dx;

  }
  if(ball -> y <= (paddle1 -> y) + PADDLE_H + 3
      && ball -> y >= paddle1 -> y
      && ball -> x <= paddle1 -> x + PADDLE_W) {
    ball -> dy = - ball -> dy;
  }
  if(ball -> y >= SCREEN_H || ball -> y < 0) {
    ball -> dy = - ball -> dy;
  }

  //Left Paddle Hit



  ball -> x += ball -> dx;
  ball -> y += ball -> dy;
}

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

  Ball ball = {SCREEN_W / 2, SCREEN_H / 2, 10, 2, 2};



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
        moveBall(&ball, &paddle1);
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
