#pragma once
#include "Component.h"
#include "DebugRenderable.h"
#include "Transform.h"
#include <memory>


class BoxCollider : public Component, public DebugRenderable
{
    public:
        BoxCollider(const Transform&);
        BoxCollider(BoxCollider* other);
        ComponentType get_component_type();
        void set_size(int, int);
        void set_offset(int, int);
        void update(){};
        SDL_Rect* get_rect();
    private:
        const Transform& m_transform;
        SDL_Rect* m_rect;
        int xOffset;
        int yOffset;
};