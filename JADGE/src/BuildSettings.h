#pragma once
#include "Scene.h"

#include <memory>
#include <vector>

class BuildSettings
{
    private:
        std::vector<std::unique_ptr<Scene>> scenes;
};