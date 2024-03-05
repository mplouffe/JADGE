#pragma once
#include <SDL.h>

class JABIRenderer
{
    public:
        JABIRenderer();
        JABIRenderer(JABIRenderer*);
        bool init(SDL_Window*);
        void close();
        void update();
    private:
        SDL_Renderer* renderer;
};