#include "GameObject.h"

void GameObject::update()
{
    for(const auto& [_, value] : components)
    {
        value->update();
    }
}

bool GameObject::addComponent(Component* component)
{
    if (components.find(component->getComponentType()) == components.end())
    {
        return components.insert(std::pair{component->getComponentType(), std::make_shared<Component>(component)}).second;
    }

    return false;
}

bool GameObject::removeComponent(ComponentType componentToRemove)
{
    return components.erase(componentToRemove) > 0;
}