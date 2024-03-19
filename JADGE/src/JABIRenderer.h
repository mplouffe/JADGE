#pragma once
#include <utility>
#include <vector>
#include <SDL.h>
#include "Renderable.h"
#include "imgui.h"

#include "backends/imgui_impl_sdlrenderer2.h"
#include "backends/imgui_impl_sdl2.h"

class JABIRenderer
{
    public:
        JABIRenderer();
        JABIRenderer(JABIRenderer&& other) noexcept : renderer(std::move(other.renderer)), io(ImGui::GetIO()){ };
        JABIRenderer(JABIRenderer*);
        ~JABIRenderer();
        bool init(SDL_Window*);
        void pre_render();
        void update(std::vector<Renderable*>);
        void render();
        SDL_Renderer* get_renderer();
    private:
        SDL_Renderer* renderer;
        ImGuiIO& io;
        ImVec4 clear_color;
};