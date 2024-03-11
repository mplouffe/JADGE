#include "GameObject.h"

#include <SDL.h>
#include <memory>
#include "Sprite.h"

GameObject::GameObject()
{
    transform = std::shared_ptr<Transform>(new Transform());
}

GameObject::GameObject(GameObject* other)
    : components(std::move(other->components)), transform(std::move(other->transform))
{ }

void GameObject::update()
{
    for(const auto& [_, value] : components)
    {
        value->update();
    }
}

bool GameObject::addComponent(ComponentType type, Component* component)
{
    if (components.find(type) == components.end())
    {
        component->set_parent(*this);
        return components.insert(std::pair{type, component}).second;
    }
    
    return false;
}

bool GameObject::removeComponent(ComponentType componentToRemove)
{
    return components.erase(componentToRemove) > 0;
}

Renderable* GameObject::get_renderables()
{
    if (components.find(ComponentType::SPRITE) != components.end())
    {
        return (Sprite*)(components.at(ComponentType::SPRITE));
    }
}

std::shared_ptr<Transform> GameObject::get_transform()
{
    return transform;
}