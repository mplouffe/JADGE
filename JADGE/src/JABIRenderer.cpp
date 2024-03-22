#include "JABIRenderer.h"


JABIRenderer::JABIRenderer()
: io(ImGui::GetIO())
{
    renderer = nullptr;
    (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

   	ImGui::StyleColorsDark();
    clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
}

JABIRenderer::JABIRenderer(JABIRenderer* other)
    : io(other->io)
{
    renderer = std::move(other->renderer);
}

JABIRenderer::~JABIRenderer()
{
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

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

    // Init ImGUI
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer2_Init(renderer);

    return true;
}

void JABIRenderer::pre_render()
{
    // Clear Screen
    SDL_SetRenderDrawColor(renderer, 0x55, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
}

void JABIRenderer::update(std::vector<Renderable*> renderables)
{
    for(auto renderable : renderables)
    {
        SDL_RenderCopy(renderer, renderable->get_texture(), renderable->get_clip(), renderable->get_render_quad());
    }
}

void JABIRenderer::debug_update(std::vector<DebugRenderable*> debug_renderables)
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    for(auto renderable : debug_renderables)
    {

        SDL_RenderDrawRect(renderer, renderable->get_rect());
    }
}

void JABIRenderer::render()
{
    ImGui::Render();
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
    // Update Screen
    SDL_RenderPresent(renderer);
}

SDL_Renderer* JABIRenderer::get_renderer()
{
    return renderer;
}