#pragma once

#include "glm/fwd.hpp"
#include "lab_m1/tema1/drawable.h"

class Projectile
{
    public:
        Projectile(glm::vec2 proj_vec, glm::vec2 proj_pos);
        ~Projectile();

        void update(float deltaTime);
        Drawable* getBody();
        bool checkCollisionTank(float tankX, float tankY, float tankSize);
        bool checkCollisionField(std::vector<float> &height_map);
        bool isEnabled();
        void disable();
        float getProjX();
        float getProjY();

    private:
        glm::vec2 proj_vec;
        glm::vec2 proj_pos;

        Drawable* body;
        bool enabled;
};
