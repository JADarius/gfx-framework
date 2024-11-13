#pragma once

#include "core/gpu/mesh.h"
#include "glm/fwd.hpp"
class Drawable {
    public:
        Drawable(Mesh* mesh);
        ~Drawable();

        glm::mat3 getModelMatrix();
        void setModelMatrix(glm::mat3 modelMatrix);
        Mesh *getMesh();

    private:
        Mesh* mesh;
        glm::mat3 modelMatrix;
};
