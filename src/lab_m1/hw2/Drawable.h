#pragma once

#include "core/gpu/mesh.h"
#include "glm/fwd.hpp"
class Drawable {
    public:
        Drawable(Mesh* mesh);
        ~Drawable();

        glm::mat4 getModelMatrix();
        void setModelMatrix(glm::mat4 modelMatrix);
        Mesh *getMesh();

    private:
        Mesh* mesh;
        glm::mat4 modelMatrix;
};
