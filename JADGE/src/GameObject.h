#pragma once

#include "Component.h"
#include "Transform.h"
#include "Renderable.h"
#include "DebugRenderable.h"
#include <memory>
#include <map>

class GameObject
{
    public:
        GameObject();
        GameObject(GameObject*);
        void update();
        bool add_component(ComponentType, Component*);
        bool remove_component(ComponentType);
        void move(int, int);
        Renderable* get_renderables();
        DebugRenderable* get_debug_renderables();
        const Transform& get_transform();
        void display_debug() const;
    private:
        std::unique_ptr<Transform> transform;
        std::map<ComponentType, Component*> components;
};