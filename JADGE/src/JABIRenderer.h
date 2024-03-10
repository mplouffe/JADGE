#pragma once
#include <utility>
#include <vector>
#include <SDL.h>
#include "Renderable.h"

class JABIRenderer
{
    public:
        JABIRenderer();
        JABIRenderer(JABIRenderer&& other) noexcept : renderer(std::move(other.renderer)){ };
        JABIRenderer(JABIRenderer*);
        ~JABIRenderer();
        bool init(SDL_Window*);
        void pre_render();
        void update(std::vector<Renderable*>);
        void render();
        SDL_Renderer* get_renderer();
    private:
        SDL_Renderer* renderer;
};