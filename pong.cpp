#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <iostream>

bool init();
void setup();
bool loop();
void kill();

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

struct racket {
  int x;
  int y;
  int width;
  int height;
} racket;

int main() {

  if (!init()) {
    return 1;
  }

  setup();

  while (loop()) {
    SDL_Delay(10);
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
  racket.x = 100;
  racket.y = 100;
  racket.width = 50;
  racket.height = 100;
}

bool loop() {
  SDL_Event e;

  // Event Loop
  while (SDL_PollEvent(&e) != 0) {
    if (e.type == SDL_QUIT) {
      return false;
    }
  }

  // Render
  // Background
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  // Racket
  SDL_Rect racket_rect = {racket.x, racket.y, racket.width, racket.height};
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderFillRect(renderer, &racket_rect);

  // Display
  SDL_RenderPresent(renderer);
  return true;
}

void kill() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
