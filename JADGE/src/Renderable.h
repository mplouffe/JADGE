#pragma once

#include <SDL.h>
#include <tuple>

class Renderable
{
    public:
        virtual SDL_Texture* get_texture() = 0;
        virtual SDL_Rect* get_clip() = 0;
        virtual const SDL_Rect * get_render_quad() = 0;
};