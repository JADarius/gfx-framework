#pragma once

#include <string>

#include "components/simple_scene.h"
#include "core/gpu/mesh.h"
#include "lab_m1/tema1/drawable.h"

class Tank
{
    public:
        Tank(float tankX, float tankSize, float turretAngle);
        ~Tank();

        void updateTank(std::vector<float> &height_map);
        std::vector<Drawable*> getParts();
        void changeTankX(float delta);
        void changeTurretAngle(float delta);
        float getTankX();
    
    private:
        float tankX, tankY;
        float tankSize;
        float turretAngle;
        float angle;

        glm::mat3 modelMatrix;
        std::vector<Drawable*> parts;
};
