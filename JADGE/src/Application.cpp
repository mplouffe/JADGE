#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <stdio.h>
#include <string>
#include <sstream>
#include <cmath>
#include <memory>

#include "BuildSettings.h"
#include "JABIRenderer.h"
#include "JABIWindow.h"

// SDL_Window* gWindow = NULL;
std::unique_ptr<JABIWindow> gWindow = NULL;
std::unique_ptr<JABIRenderer> gRenderer = NULL;

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

	gWindow = std::make_unique<JABIWindow>(new JABIWindow());
	gRenderer = std::make_unique<JABIRenderer>(new JABIRenderer());
	
	if (!gWindow->init())
	{
		return false;
	}

	if (!gRenderer->init(gWindow->get_window()))
	{
		return false;
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

	// Destroy window
	gRenderer->close();
	gWindow->close();
	
	gWindow = NULL;
	gRenderer = NULL;

	// Quit SDL subsystems
	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[])
{
	//Initialize SDL
	if(!init())
	{
		SDL_Log("Failed to initialize.\n");
		return 0;
	}

	SDL_Event e;
	bool quit = false;

	while(!quit)
	{
		while(SDL_PollEvent(&e))
		{ 
			if(e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		gRenderer->update();
	}

	return 0;
}

