#pragma once

#include "components/simple_scene.h"
#include "glm/fwd.hpp"
#include "lab_m1/tema1/projectile.h"
#include "lab_m1/tema1/tank.h"
#include <vector>

namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
     public:
        Tema1();
        ~Tema1();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

     protected:
        glm::mat3 modelMatrix;
        std::vector<float> height_map;
        std::vector<float> height_map_background;

        float tankX, tankY;
        float tankSize;
        float turretAngle;

        float angle;

        Tank firstTank;
        Tank secondTank;

        std::vector<Projectile> projectiles;
    };
}   // namespace m1
