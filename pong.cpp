#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>
#include <iostream>

int main() {

  SDL_Surface *winSurface = NULL;
  SDL_Window *window = NULL;

  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cerr << "Error initializing SDL : " << SDL_GetError() << std::endl;
    system("pause");
    return 1;
  }

  window =
      SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                       800, 800, SDL_WINDOW_SHOWN);
  if (!window) {
    std::cerr << "Error creating window :" << SDL_GetError() << std::endl;
    system("pause");
    return 1;
  }

  winSurface = SDL_GetWindowSurface(window);
  if (!winSurface) {
    std::cerr << "Error getting surface :" << SDL_GetError() << std::endl;
    system("pause");
    return 1;
  }

  bool quit = false;
  SDL_Event e;

  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
