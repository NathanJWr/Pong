#include <SDL2/SDL.h>
#include "structs.h"
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

