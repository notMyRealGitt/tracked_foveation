#include <iostream>

#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

struct Ctx {
  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;
};

struct MousePos {
  float x;
  float y;
};

static Ctx ctx;
static MousePos mouse_pos;

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
  if(!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  if(!SDL_CreateWindowAndRenderer("mouse track display", 640, 480, SDL_WINDOW_RESIZABLE, &ctx.window, &ctx.renderer)) {
    SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  SDL_SetRenderLogicalPresentation(ctx.renderer, 640, 480, SDL_LOGICAL_PRESENTATION_LETTERBOX);

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
  switch(event->type) {
    case SDL_EVENT_MOUSE_MOTION: {
      SDL_FRect rect;
      SDL_SetRenderDrawColor(ctx.renderer, 100, 33, 33, SDL_ALPHA_OPAQUE);
      SDL_RenderClear(ctx.renderer);
      SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
      rect.x = mouse_pos.x;
      rect.y = mouse_pos.y;
      rect.w = 20;
      rect.h = 20;
      SDL_SetRenderDrawColor(ctx.renderer, 10, 140, 140, SDL_ALPHA_OPAQUE);
      if(!SDL_RenderFillRect(ctx.renderer, &rect)) {
        SDL_Log("STFNDBG");
      }
      SDL_RenderPresent(ctx.renderer);
      return SDL_APP_CONTINUE;
    }
    case SDL_EVENT_WINDOW_MOUSE_LEAVE: {
      SDL_SetRenderDrawColor(ctx.renderer, 15, 15, 15, SDL_ALPHA_OPAQUE);
      SDL_RenderClear(ctx.renderer);
      SDL_RenderPresent(ctx.renderer);
      return SDL_APP_CONTINUE;
    }
    case SDL_EVENT_QUIT: {
      return SDL_APP_SUCCESS;
    }
    default: {
      return SDL_APP_CONTINUE;
    }
  }
}


SDL_AppResult SDL_AppIterate(void* appstate) {
  // ... nothing yet
  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
  // ... nothing yet
}