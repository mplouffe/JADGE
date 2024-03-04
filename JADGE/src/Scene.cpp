#include "Scene.h"

void Scene::update()
{
    for(const auto gameObject : gameObjects)
    {
        gameObject->update();
    }
}