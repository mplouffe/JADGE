#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

// IMGUI
#include "backends/imgui_impl_sdl2.h"

#include <stdio.h>
#include <string>
#include <sstream>
#include <cmath>
#include <memory>

#include "BuildSettings.h"
#include "JABIRenderer.h"
#include "JABIWindow.h"
#include "JABIGUI.h"

// Audio
// - Music
// Mix_Music *gMusic;
// - SFX
Mix_Chunk *gSelect;

// Input
SDL_Joystick* gGameController = NULL;

bool init()
{
	// Initialzation flag
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
	{
		SDL_Log( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	// set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		SDL_Log("Warning: Linear texture filtering not enabled!");
	}

	// check for joysticks
	if(SDL_NumJoysticks() < 1)
	{
		SDL_Log("Warning: No joysticks connected!\n");
	}
	else
	{
		// Load joystick
		gGameController = SDL_JoystickOpen(0);
		if(gGameController == NULL)
		{
			SDL_Log("Unable to open game controller! SDL_Error: %s\n", SDL_GetError());
		}
	}

	// Initalize SDL_mixer
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		SDL_Log("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	// Initalize SDL_ttf
	if(TTF_Init() == -1)
	{
		SDL_Log("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}

	// Context needs to be created prior to making a JABIGUI
    IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	
	return success;
}

void close()
{
	// free audio
	Mix_FreeChunk(gSelect);
	gSelect = NULL;

	// close game controller
	SDL_JoystickClose(gGameController);
	gGameController = NULL;

	// Quit SDL subsystems
	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
} 

int main(int argc, char* [])
{
	//Initialize SDL
	if(!init())
	{
		SDL_Log("Failed to initialize SDL.\n");
		return 0;
	}

	auto window = std::make_unique<JABIWindow>(new JABIWindow());
	auto renderer = std::make_unique<JABIRenderer>(new JABIRenderer());
	auto imgui = std::make_unique<JABIGUI>(new JABIGUI());

	if (!window->init())
	{
		SDL_Log("Failed to initialize window.\n");
		return 0;
	}

	if (!renderer->init(window->get_window()))
	{
		SDL_Log("Failed to initialize renderer.\n");
		return 0;
	}

	imgui->init(window->get_window(), renderer->get_renderer());

	SDL_Event e;
	bool quit = false;

	while(!quit)
	{
		while(SDL_PollEvent(&e))
		{ 
			ImGui_ImplSDL2_ProcessEvent(&e);
			if(e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		imgui->render();
		renderer->update();
	}

	close();
	return 0;
}

