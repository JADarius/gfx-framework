#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{

    // Create square with given bottom left corner, length and color
    Mesh* CreateCeva(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);

    Mesh* CreateTankFirstBase(const std::string &name, glm::vec3 center, glm::vec3 color, float length);
    Mesh* CreateTankSecondBase(const std::string &name, glm::vec3 center, glm::vec3 color, float length);
    Mesh* CreateTankTop(const std::string &name, glm::vec3 center, glm::vec3 color, float radius);
    Mesh* CreateTank(const std::string &name, glm::vec3 center, glm::vec3 color, float length, float radius);
}
