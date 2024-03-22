#pragma once

#include <SDL.h>

class DebugRenderable
{
    public:
        virtual SDL_Rect* get_rect() = 0;      
};