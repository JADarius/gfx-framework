#include "lab_m1/tema1/tema1.h"

#include <algorithm>
#include <cmath>
#include <vector>
#include <iostream>

#include "glm/fwd.hpp"
#include "lab_m1/tema1/transform2D.h"
#include "lab_m1/tema1/object2D.h"
#include "utils/gl_utils.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */

std::vector<float> gen_heights(int length) {
    std::vector<float> height_map(length);
    for (int x = 0; x < length; x++) {
        height_map[x] = 50 * glm::sin(0.1 * x) + 50 * glm::sin(0.2 * x) +  350;
    }
    return height_map;
}

Tema1::Tema1()
{
    glm::ivec2 resolution = window->GetResolution();
    height_map = gen_heights(resolution.x / 10 + 1);
    tankX = 302;
    tankSize = 5;
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);
    float squareSide = 1;

    cx = (corner.x + squareSide) / 2;
    cy = (corner.y + squareSide) / 2;

    // Initialize tx and ty (the translation steps)
    translateX = 0;
    translateY = 0;

    // Initialize sx and sy (the scale factors)
    scaleX = 1;
    scaleY = 1;

    // Initialize angularStep
    angularStep = 0.5;

    Mesh* square1 = object2D::CreateCeva("square", corner, squareSide, glm::vec3(225.0 / 255, 235.0 / 255, 33.0 / 255), true);
    AddMeshToList(square1);
    Mesh* firstBase = object2D::CreateTankFirstBase("firstBase", glm::vec3(0, 0, 0), glm::vec3(116.0 / 255, 100.0 / 255, 78.0 / 255), tankSize);
    AddMeshToList(firstBase);
    Mesh* secondBase = object2D::CreateTankSecondBase("secondBase", glm::vec3(0, 0, 0), glm::vec3(204.0 / 255, 175.0 / 255, 136.0 / 255), tankSize);
    AddMeshToList(secondBase);
    Mesh* top = object2D::CreateTankTop("top", glm::vec3(0, 0, 0), glm::vec3(204.0 / 255, 175.0 / 255, 136.0 / 255), 2.5 * tankSize);
    AddMeshToList(top);
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
    glClearColor(135.0 / 255, 206.0 / 255, 235.0 / 255, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Field
    for (int index = 0; index < height_map.size() - 1; index++) {
        modelMatrix = glm::mat3(1); 
        modelMatrix *= transform2D::Translate((index) * 10, height_map[index]);
        modelMatrix *= transform2D::Shear(index * 10, height_map[index], (index + 1) * 10, height_map[index + 1]);
        modelMatrix *= transform2D::Scale(10, std::max(height_map[index], height_map[index + 1]));
        RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);
    }

    // Tank 
    // Calculate Y
    float Ax = glm::ceil(tankX / 10) * 10; 
    float Bx = glm::floor(tankX / 10) * 10; 
    float t = (tankX - Ax) / (Bx - Ax);
    float tankY = height_map[Ax / 10] + t * (height_map[Bx / 10] - height_map[Ax / 10]);

    // Calculate rotation
    float Vx = Bx - Ax;
    float Vy = height_map[Bx / 10] - height_map[Ax / 10];
    float angle = glm::atan2(-Vy, -Vx);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(tankX, tankY);
    modelMatrix *= transform2D::Rotate(angle);
    RenderMesh2D(meshes["firstBase"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(tankX, tankY);
    modelMatrix *= transform2D::Rotate(angle);
    modelMatrix *= transform2D::Translate(0, tankSize);
    RenderMesh2D(meshes["secondBase"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(tankX, tankY);
    modelMatrix *= transform2D::Rotate(angle);
    modelMatrix *= transform2D::Translate(0, 3 * tankSize);
    RenderMesh2D(meshes["top"], shaders["VertexColor"], modelMatrix);
}


void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
    float speed = 200;
    if (window->KeyHold(GLFW_KEY_A)) {
        tankX -= speed * deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_D)) {
        tankX += speed * deltaTime;
    }
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
