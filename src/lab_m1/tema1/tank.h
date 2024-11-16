#pragma once

#include <string>

#include "components/simple_scene.h"
#include "core/gpu/mesh.h"
#include "lab_m1/tema1/drawable.h"
#include "lab_m1/tema1/projectile.h"

class Tank
{
    public:
        Tank(float tankX, float tankSize, float turretAngle, glm::vec3 color);
        ~Tank();

        void updateTank(std::vector<float> &height_map, float deltaTime);
        std::vector<Drawable*> getParts();
        void changeTankX(float delta);
        void changeTurretAngle(float delta);
        float getTankX();
        float getTankY();
        float getTankSize();
        Projectile fireProj();
        void hit();
        bool isAlive();
        void simulateTrajectory();
    
    private:
        float tankX, tankY;
        float tankSize;
        float turretAngle;
        float angle;
        glm::vec2 proj_vec;
        glm::vec2 proj_pos;

        glm::mat3 modelMatrix;
        std::vector<Drawable*> parts;
        int hitpoints;

};
