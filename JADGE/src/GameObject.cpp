#include "GameObject.h"

#include <SDL.h>
#include <memory>
#include "Sprite.h"
#include "imgui.h"

GameObject::GameObject()
{
    transform = std::unique_ptr<Transform>(new Transform());
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

bool GameObject::add_component(ComponentType type, Component* component)
{
    if (components.find(type) == components.end())
    {
        return components.insert(std::pair{type, component}).second;
    }
    
    return false;
}

bool GameObject::remove_component(ComponentType componentToRemove)
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

const Transform& GameObject::get_transform()
{
    return *transform;
}

void GameObject::move(int x, int y)
{
    transform->move_position(x, y);
}

void GameObject::display_debug() const
{
    if (transform == NULL)
    {
        return;
    }

    int x;
    int y;
    std::tie(x, y) = transform.get()->get_position();
    
    ImGui::NewFrame();
    ImGui::Begin("lvl_0 game engine");
    ImGui::Text("It's Chewie!!! \\O.o/");
    ImGui::DragInt("X: ", &x, 1);
    ImGui::DragInt("Y: ", &y, 1);
    ImGui::End();

    transform.get()->move_position(x, y);
}