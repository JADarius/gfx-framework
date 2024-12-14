#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object3D
{

    // Create square with given bottom left corner, length and color
    Mesh* createCube(glm::vec3 center, glm::vec3 color, float length);
    Mesh* createRectCuboid(glm::vec3 center, glm::vec3 color, float lengthOx, float lengthOy, float lengthOz);
    Mesh* createCylinder(glm::vec3 center, glm::vec3 color, float radius, float height);
    Mesh* createCone(glm::vec3 center, glm::vec3 color, float radius, float height);
}
