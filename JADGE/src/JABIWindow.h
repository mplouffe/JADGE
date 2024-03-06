#pragma once
#include <SDL.h>

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

class JABIWindow
{
    public:
        JABIWindow();
        JABIWindow(JABIWindow*);
        ~JABIWindow();
        bool init();
        SDL_Window* get_window();
    private:
        SDL_Window* window;
};