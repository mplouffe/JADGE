#pragma once

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
        virtual ComponentType getComponentType() = 0;
        virtual void update() = 0;
};