#include "BoxCollider.h"

BoxCollider::BoxCollider(const Transform& parent_transform)
 : m_transform(parent_transform)
{
    m_rect = nullptr;
}

BoxCollider::BoxCollider(BoxCollider* other)
 : m_transform(other->m_transform), m_rect(std::move(other->m_rect))
 { }

ComponentType BoxCollider::get_component_type()
{
    return ComponentType::BOX_COLLIDER;
}

void BoxCollider::set_size(int width, int height)
{
    int x, y;
    std::tie(x, y) = m_transform.get_position();
    m_rect = new SDL_Rect({x, y, width, height});
}

SDL_Rect* BoxCollider::get_rect()
{
    if (m_rect == nullptr)
    {
        SDL_Log("Returning null");
        return m_rect;
    }

    SDL_Log("About to tie");
    std::tie(m_rect->x, m_rect->y) = m_transform.get_position();
    return m_rect;
}