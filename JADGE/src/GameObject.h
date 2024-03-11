#pragma once

#include "Component.h"
#include "Transform.h"
#include "Renderable.h"
#include <memory>
#include <map>

class GameObject
{
    public:
        GameObject();
        GameObject(GameObject*);
        void update();
        bool addComponent(ComponentType, Component*);
        bool removeComponent(ComponentType);
        Renderable* get_renderables();
        std::shared_ptr<Transform> get_transform();
    private:
        std::shared_ptr<Transform> transform;
        std::map<ComponentType, Component*> components;
};