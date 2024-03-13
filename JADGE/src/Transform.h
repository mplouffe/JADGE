#pragma once
#include "Component.h"

class GameObject;

#include <vector>

class Transform : public Component
{
    public:
        Transform();
        Transform(Transform*);
        ComponentType getComponentType();
        const std::tuple<int, int> getPosition();
        void movePosition(int, int);
        void movePosition(std::tuple<int, int>);
        void update();
        void set_parent(GameObject&);
    private:
        int mX;
        int mY;
};