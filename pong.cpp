#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <iostream>

bool init();
void setup();
bool loop();
void kill();

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

Uint32 lastUpdate = 0;

struct racket {
  float x, y, velocity;
  int width, height;
};

racket playerRacket, opponentRacket;

int main() {

  if (!init()) {
    return 1;
  }

  setup();

  while (loop()) {
  }

  kill();
  return 0;
}

bool init() {

  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
    system("pause");
    return false;
  }

  window =
      SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                       800, 800, SDL_WINDOW_SHOWN);
  if (!window) {
    std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
    system("pause");
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    std::cerr << "Error creating renderer: " << SDL_GetError() << std::endl;
    system("pause");
    return false;
  }

  return true;
}

void setup() {
  playerRacket.x = 100;
  playerRacket.y = 100;
  playerRacket.width = 50;
  playerRacket.height = 100;
  playerRacket.velocity = 0;

  opponentRacket.x = 700;
  opponentRacket.y = 700;
  opponentRacket.width = 50;
  opponentRacket.height = 100;
  opponentRacket.velocity = 0;
}

bool loop() {
  SDL_Event e;

  // Event Loop
  while (SDL_PollEvent(&e) != 0) {
    if (e.type == SDL_QUIT) {
      return false;
    }

    if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
      case SDLK_UP:
        playerRacket.velocity = -100.0f;
        break;
      case SDLK_DOWN:
        playerRacket.velocity = 100.0f;
        break;
      }
    }

    if (e.type == SDL_KEYUP) {
      if (!(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP] ||
            SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN])) {
        playerRacket.velocity = 0;
      }
    }
  }

  // Physics Loop
  Uint32 time = SDL_GetTicks();
  float deltaTime = (time - lastUpdate) / 1000.0f;
  lastUpdate = time;

  playerRacket.y += playerRacket.velocity * deltaTime;

  // Render
  // Background
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  // Racket
  SDL_Rect playerRacketRect = {(int)playerRacket.x, (int)playerRacket.y,
                               playerRacket.width, playerRacket.height};
  SDL_Rect opponentRacketRect = {(int)opponentRacket.x, (int)opponentRacket.y,
                                 opponentRacket.width, opponentRacket.height};
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderFillRect(renderer, &playerRacketRect);
  SDL_RenderFillRect(renderer, &opponentRacketRect);

  // Display
  SDL_RenderPresent(renderer);
  return true;
}

void kill() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
