#include "Component.h"
#include "Transform.h"

class GameObject
{
    public:
        void Update();
    private:
        Transform mTransform;
        Component* mComponents;
};