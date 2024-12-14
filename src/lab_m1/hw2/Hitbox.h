#pragma once

#include "core/gpu/mesh.h"
#include "glm/fwd.hpp"
class Hitbox {
    public:
        Hitbox(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);
        ~Hitbox();

        float getXMin();
        float getXMax();
        float getYMin();
        float getYMax();
        float getZMin();
        float getZMax();
    private:
        float xMin, xMax, yMin, yMax, zMin, zMax;
};
