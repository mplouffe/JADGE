#pragma once
#include "GameObject.h"

#include <memory>

class Scene
{
    public:
        void update();
    private:
        std::vector<std::shared_ptr<GameObject>> gameObjects;
};