#include "Scene.h"

Scene::Scene()
{ }

Scene::Scene(Scene* other)
: gameObjects(std::move(other->gameObjects))
{ }

void Scene::add_gameobject(GameObject* new_game_object)
{
    gameObjects.insert(gameObjects.end(), std::make_unique<GameObject>(new_game_object));
}

void Scene::update()
{
    for(const auto gameObject : gameObjects)
    {
        gameObject->update();
    }
}

void Scene::display_debug()
{
    for(const auto gameObject : gameObjects)
    {
        gameObject->display_debug();
    }
}

std::vector<Renderable*> Scene::get_renderables()
{
    std::vector<Renderable*> renderables;
    for(const auto gameObject : gameObjects)
    {
        auto renderable = gameObject->get_renderables();
        if (renderable != nullptr)
        {
            renderables.insert(renderables.end(), renderable);
        }
    }

    return renderables;
}