#pragma once

#include "Component.h"
#include "Transform.h"
#include <memory>
#include <map>

class GameObject
{
    public:
        void update();
        bool addComponent(Component*);
        bool removeComponent(ComponentType);
    private:
        std::unique_ptr<Transform> transform;
        std::map<ComponentType, std::shared_ptr<Component>> components;
};