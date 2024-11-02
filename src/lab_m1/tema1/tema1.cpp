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
        height_map[x] = 50 * glm::sin(0.1 * x) + 50 * glm::sin(0.2 * x) + 75 * glm::sin(0.4 * x) + 200;
    }
    return height_map;
}

Tema1::Tema1()
{
    unscale = false;
    glm::ivec2 resolution = window->GetResolution();
    height_map = gen_heights(resolution.x / 10 + 1);
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

    // TODO(student): Compute coordinates of a square's center, and store
    // then in the `cx` and `cy` class variables (see the header). Use
    // `corner` and `squareSide`. These two class variables will be used
    // in the `Update()` function. Think about it, why do you need them?

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

    Mesh* square1 = object2D::CreateCeva("square1", corner, squareSide, glm::vec3(1, 0.5, 0), true);
    AddMeshToList(square1);

    Mesh* square2 = object2D::CreateCeva("square2", corner, squareSide, glm::vec3(0, 1, 0));
    AddMeshToList(square2);

    Mesh* square3 = object2D::CreateCeva("square3", corner, squareSide, glm::vec3(0, 0, 1));
    AddMeshToList(square3);

    Mesh* top = object2D::CreateCeva("top", corner, squareSide, glm::vec3(1, 0, 0), true);
    AddMeshToList(top);

    Mesh* mid = object2D::CreateCeva("mid", corner, squareSide, glm::vec3(1, 0, 0), true);
    AddMeshToList(mid);

    Mesh* wheelL = object2D::CreateCeva("wheelL", corner, squareSide, glm::vec3(0, 0, 1), true);
    AddMeshToList(wheelL);

    Mesh* wheelR = object2D::CreateCeva("wheelR", corner, squareSide, glm::vec3(0, 0, 1), true);
    AddMeshToList(wheelR);
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
    // translateX += deltaTimeSeconds * 100;
    // translateY += deltaTimeSeconds * 100;
    //
    // modelMatrix = glm::mat3(1);
    // modelMatrix *= transform2D::Translate(translateX, translateY);
    // RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);
    //
    // scaleX += 0.1;
    // scaleY += 0.1;
    //
    // modelMatrix = glm::mat3(1);
    // modelMatrix *= transform2D::Translate(400 + cx, 250 + cy) * transform2D::Scale(scaleX, scaleY) * transform2D::Translate(-cx, -cy);
    //
    // RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
    //
    // angularStep += 0.1;
    //
    // modelMatrix = glm::mat3(1);
    // modelMatrix *= transform2D::Translate(650 + cx, 250 + cy) * transform2D::Rotate(angularStep) * transform2D::Shear(0, 0, 5, 2) * transform2D::Translate(-cx, -cy);
    //
    // RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);
    //
    // modelMatrix = glm::mat3(1);
    // modelMatrix *= transform2D::Translate(carX + 200, carY + 200);
    // RenderMesh2D(meshes["top"], shaders["VertexColor"], modelMatrix);
    //
    // modelMatrix = glm::mat3(1);
    // modelMatrix *= transform2D::Translate(carX + 250, carY + 150) * transform2D::Scale(3, 1) * transform2D::Translate(-cx, -cy);
    // RenderMesh2D(meshes["mid"], shaders["VertexColor"], modelMatrix);
    //
    // modelMatrix = glm::mat3(1);
    // modelMatrix *= transform2D::Translate(carX + 150, carY + 50) * transform2D::Rotate(wheelRot) * transform2D::Translate(-cx, -cy);
    // RenderMesh2D(meshes["wheelL"], shaders["VertexColor"], modelMatrix);
    // 
    // modelMatrix = glm::mat3(1);
    // modelMatrix *= transform2D::Translate(carX + 350, carY + 50) * transform2D::Rotate(wheelRot) * transform2D::Translate(-cx, -cy);
    // RenderMesh2D(meshes["wheelR"], shaders["VertexColor"], modelMatrix);
    for (int index = 0; index < height_map.size() - 1; index++) {
        modelMatrix = glm::mat3(1); 
        // modelMatrix *= transform2D::Translate((index) * 10, height_map[index]) * transform2D::Shear(index * 10, height_map[index], (index + 1) * 10, height_map[index + 1]) * transform2D::Scale(10, std::max(height_map[index], height_map[index + 1]));
        modelMatrix *= transform2D::Translate((index) * 10, height_map[index]);
        modelMatrix *= transform2D::Shear(index * 10, height_map[index], (index + 1) * 10, height_map[index + 1]);
        modelMatrix *= transform2D::Scale(10, std::max(height_map[index], height_map[index + 1]));
        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);
    }
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
    if (window->KeyHold(GLFW_KEY_A)) {
        carX -= 10; 
        wheelRot += 0.1;
    }
    if (window->KeyHold(GLFW_KEY_D)) {
        carX += 10; 
        wheelRot -= 0.1;
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
