#pragma once

class GameObject;

enum ComponentType
{
    TRANSFORM,
	// BOX_COLLIDER,
    // PHYSICBODY,
    SPRITE,
};

class Component
{
    public:
        virtual ComponentType get_component_type() = 0;
        virtual void update() = 0;
        virtual void set_parent(GameObject&) = 0;
};