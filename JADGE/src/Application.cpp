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

#include "JABIRenderer.h"
#include "JABIWindow.h"
#include "JABIGUI.h"
#include "JABIControls.h"
#include "Sprite.h"
#include "Scene.h"
#include "GameObject.h"

// Audio
// - Music
// Mix_Music *gMusic;
// - SFX
Mix_Chunk *gSelect;

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
	auto controls = std::make_unique<JABIControls>(new JABIControls());

	if (!window->init()) return 0;
	if (!renderer->init(window->get_window())) return 0;
	imgui->init(window->get_window(), renderer->get_renderer());
	controls->init();

	auto scene = std::make_unique<Scene>(new Scene());
	auto gameObject = new GameObject();
	auto sprite = new Sprite();
	sprite->loadFromFile("../assets/sprites/plane.png", renderer->get_renderer());
	gameObject->addComponent(ComponentType::SPRITE, sprite);
	scene->add_gameobject(gameObject);

	bool quit = false;
	while(!quit)
	{
		controls->update(quit);
		scene->update();
		imgui->render();
		renderer->pre_render();
		renderer->update(scene->get_renderables());
		renderer->render();
	}

	close();
	return 0;
}

