#pragma once
#include "GameObject.h"
#include "Renderable.h"

#include <memory>

class Scene
{
    public:
        Scene();
        Scene(Scene*);
        void add_gameobject(GameObject*);
        void update();
        void display_debug();
        std::vector<Renderable*> get_renderables();
    private:
        std::vector<std::shared_ptr<GameObject>> gameObjects;
};