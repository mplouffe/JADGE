#pragma once
#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_sdlrenderer2.h"

class JABIGUI
{
    public:
        JABIGUI();
        JABIGUI(JABIGUI*);
        ~JABIGUI();
        void init(SDL_Window*, SDL_Renderer*);
        void render();
    private:
        ImGuiIO& io;
        ImVec4 clear_color;
        int counter;
        float f;
        bool checkbox_demo;
};