#include "JABIWindow.h"

JABIWindow::JABIWindow()
{
    window = NULL;
}

JABIWindow::JABIWindow(JABIWindow*)
{ 
    window = NULL;
}

bool JABIWindow::init()
{
    window = SDL_CreateWindow("JADGE: Just Another Dumb Game Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

    if (window == NULL)
    {
        SDL_Log("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void JABIWindow::close()
{
    SDL_DestroyWindow(window);
}

SDL_Window* JABIWindow::get_window()
{
    return window;
}