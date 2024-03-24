#include "JABIControls.h"
#include "backends/imgui_impl_sdl2.h"

JABIControls::JABIControls()
{
    function_map = std::map<Uint32, std::function<void()>>();
    function_map.insert_or_assign(SDL_EventType::SDL_KEYDOWN, [&, this](){ this->handle_keydown(); });
    function_map.insert_or_assign(SDL_EventType::SDL_JOYAXISMOTION, [&, this](){ SDL_Log("Does this actually work?");});
}

JABIControls::JABIControls(JABIControls* other)
{
    function_map = std::move(other->function_map);
}

JABIControls::~JABIControls()
{
    // close game controller
	SDL_JoystickClose(game_controller);
	game_controller = NULL;
}

void JABIControls::init()
{
    // check for joysticks
	if(SDL_NumJoysticks() < 1)
	{
		SDL_Log("Warning: No joysticks connected!\n");
	}
	else
	{
		// Load joystick
        game_controller = SDL_JoystickOpen(0);
        if(game_controller == NULL)
        {
            SDL_Log("Unable to open game controller! SDL_Error: %s\n", SDL_GetError());
        }
	}
}

void JABIControls::handle_keydown()
{
    /// SDL_Log("Can I even handle this?");
}

void JABIControls::update(bool& quit, bool& display_debug)
{
    while(SDL_PollEvent(&e))
    {
        if (display_debug) ImGui_ImplSDL2_ProcessEvent(&e);

        if (auto search = function_map.find(e.type); search != function_map.end())
        {
            (function_map.at(e.type))();
        }

        if(e.type == SDL_QUIT)
        {
            quit = true;
        }

        if(e.type == SDL_KEYDOWN)
        {
            switch(e.key.keysym.sym)
            {
                case SDLK_HOME:
                    display_debug = !display_debug;
                    break;
            }
        }
    }
}