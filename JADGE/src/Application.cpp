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
#include "JABIControls.h"
#include "Sprite.h"
#include "Scene.h"
#include "GameObject.h"
#include "BoxCollider.h"

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
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0"))
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

	// Start the Engine
	auto window = std::make_unique<JABIWindow>(new JABIWindow());
	auto renderer = std::make_unique<JABIRenderer>(new JABIRenderer());
	auto controls = std::make_unique<JABIControls>(new JABIControls());

	if (!window->init()) return 0;
	if (!renderer->init(window->get_window())) return 0;
	controls->init();
	// VrOOm VrOOm.

	// Create the Game World
	auto scene = std::make_unique<Scene>(new Scene());
	auto gameObject = new GameObject();
	auto sprite = new Sprite(gameObject->get_transform());
	sprite->load_from_file("../assets/sprites/ChewieSpriteSheet.png", renderer->get_renderer());

	auto spriteAnimator = new SpriteAnimator();
	auto keyframes = new std::vector<AnimationKeyFrame>();
	keyframes->push_back({0, 8});
	keyframes->push_back({1, 8});
	keyframes->push_back({2, 8});
	keyframes->push_back({1, 8});

	auto frames = new std::vector<SDL_Rect>();
	frames->push_back({0, 0, 36, 36});
	frames->push_back({36, 0, 36, 36});
	frames->push_back({72, 0, 36, 36});

	spriteAnimator->set_keyframes(*keyframes);
	spriteAnimator->set_frames(*frames);

	sprite->add_animator(spriteAnimator);
	sprite->set_size(150, 150);
	gameObject->add_component(ComponentType::SPRITE, sprite);

	auto box_collider = new BoxCollider(gameObject->get_transform());
	box_collider->set_size(150, 150);
	gameObject->add_component(ComponentType::BOX_COLLIDER, box_collider);

	gameObject->move(130, 150);

	scene->add_gameobject(gameObject);

	// bEEp bOOp

	// Games Games Games
	bool quit = false;
	while(!quit)
	{
		controls->update(quit);
		scene->update();
		renderer->pre_render();
		scene->display_debug();
		renderer->update(scene->get_renderables());
		SDL_Log("about to debug update");
		renderer->debug_update(scene->get_debug_renderables());
		renderer->render();
	}
	// Win Win Win!!!

	close();
	return 0;
}

