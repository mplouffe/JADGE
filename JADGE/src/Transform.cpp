#include "Transform.h"
#include "GameObject.h"

Transform::Transform()
{
    mX = 0;
    mY = 0;
}

Transform::Transform(Transform* other)
 : mX(other->mX), mY(other->mY) { };

ComponentType Transform::get_component_type()
{
    return ComponentType::TRANSFORM;
}

const std::tuple<int, int> Transform::getPosition()
{
    return {mX, mY};
}

void Transform::movePosition(std::tuple<int, int> aNewPosition)
{
    std::tie(mX, mY) = aNewPosition;
}

void Transform::movePosition(int newX, int newY)
{
    mX = newX;
    mY = newY;
}

void Transform::update() {};

void Transform::set_parent(GameObject& _) {};