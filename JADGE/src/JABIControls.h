#pragma once
#include <map>
#include <functional>
#include <SDL.h>

class JABIControls
{
    public:
        JABIControls();
        JABIControls(JABIControls*);
        ~JABIControls();
        void init();
        void update(bool& quit);
        void handle_keydown();
    private:
        SDL_Event e;
        std::map<Uint32, std::function<void()>> function_map;
        SDL_Joystick* game_controller;
};