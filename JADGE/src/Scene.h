#pragma once
#include "GameObject.h"
#include "Renderable.h"
#include "DebugRenderable.h"
#include "BoxCollider.h"

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
        std::vector<DebugRenderable*> get_debug_renderables();
    private:
        std::vector<std::shared_ptr<GameObject>> gameObjects;
};