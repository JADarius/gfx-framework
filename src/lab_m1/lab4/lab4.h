#pragma once

#include "components/simple_scene.h"

#include "Field.h"
#include "Drone.h"
#include "Tree.h"
#include "object3D.h"

namespace m1
{
    class Lab4 : public gfxc::SimpleScene
    {
     public:
        struct ViewportArea
        {
            ViewportArea() : x(0), y(0), width(1), height(1) {}
            ViewportArea(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        Lab4();
        ~Lab4();

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

        void RenderScene();
        void RenderMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix) override;
        void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix);

        glm::vec3 generatePackage();
        glm::vec3 generatePad();
     protected:
        glm::mat4 modelMatrix;
        glm::mat4 projectionMatrix;
        glm::vec3 package_position;
        glm::vec3 pad_position;
        GLenum polygonMode;
        ViewportArea miniViewportArea;
        Field* field;
        Drone* drone;
        Drawable* package;
        Mesh* package_mesh;
        Drawable* deliver_pad;
        Mesh* deliver_pad_mesh;
        std::vector<Tree*> treeList;
        bool in_transit;
        int delivered_packages;
    };
}   // namespace m1

