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
        const std::tuple<int, int> get_position() const;
        void move_position(int, int);
        void move_position(std::tuple<int, int>);
        void update();
    private:
        int mX;
        int mY;
};