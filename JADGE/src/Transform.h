#pragma once
#include "Component.h"

class GameObject;

#include <vector>

class Transform : public Component
{
    public:
        Transform();
        Transform(Transform*);
        ComponentType get_component_type();
        const std::tuple<int, int> getPosition();
        void movePosition(int, int);
        void movePosition(std::tuple<int, int>);
        void update();
        void set_parent(GameObject&);
    private:
        int mX;
        int mY;
};