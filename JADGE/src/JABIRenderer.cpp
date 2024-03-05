#include "JABIRenderer.h"

JABIRenderer::JABIRenderer()
{
    renderer = NULL;
}

JABIRenderer::JABIRenderer(JABIRenderer* other)
{
    renderer = NULL;
}

bool JABIRenderer::init(SDL_Window* window)
{
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        SDL_Log("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }
    // Initialize renderer color
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    return true;
}

void JABIRenderer::close()
{
    SDL_DestroyRenderer(renderer);
}

void JABIRenderer::update()
{
    // Clear Screen
    SDL_SetRenderDrawColor(renderer, 0x55, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    // Update Screen
    SDL_RenderPresent(renderer);
}