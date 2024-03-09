#pragma once
#include <utility>
#include <SDL.h>

class JABIRenderer
{
    public:
        JABIRenderer();
        JABIRenderer(JABIRenderer&& other) noexcept : renderer(std::move(other.renderer)){ };
        JABIRenderer(JABIRenderer*);
        ~JABIRenderer();
        bool init(SDL_Window*);
        void update();
        SDL_Renderer* get_renderer();
    private:
        SDL_Renderer* renderer;
};