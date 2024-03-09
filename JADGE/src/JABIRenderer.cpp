#include "JABIRenderer.h"
#include <utility>

#include "imgui.h"
#include "backends/imgui_impl_sdlrenderer2.h"

JABIRenderer::JABIRenderer()
{
    renderer = nullptr;
}

JABIRenderer::JABIRenderer(JABIRenderer* other)
{
    renderer = std::move(other->renderer);
}

JABIRenderer::~JABIRenderer()
{
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
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

void JABIRenderer::update()
{
    // Clear Screen
    SDL_SetRenderDrawColor(renderer, 0x55, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());

    // Update Screen
    SDL_RenderPresent(renderer);
}

SDL_Renderer* JABIRenderer::get_renderer()
{
    return renderer;
}