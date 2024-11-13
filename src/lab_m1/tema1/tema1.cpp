#include "lab_m1/tema1/tema1.h"

#include <algorithm>
#include <cmath>
#include <vector>
#include <iostream>

#include "glm/ext/scalar_constants.hpp"
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

Tema1::Tema1() : firstTank(Tank(501, 5, 0))
{
    glm::ivec2 resolution = window->GetResolution();
    height_map = gen_heights(resolution.x / 10 + 1);
    tankX = 302;
    tankSize = 5;
    turretAngle = 0;
    fired_proj = false;
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

    Mesh* square = object2D::CreateCeva("square", corner, squareSide, glm::vec3(225.0 / 255, 235.0 / 255, 33.0 / 255), true);
    AddMeshToList(square);
    Mesh* proj = object2D::CreateCeva("proj", corner, 10, glm::vec3(0, 0, 0), true);
    AddMeshToList(proj);
    // Mesh* firstBase = object2D::CreateTankFirstBase("firstBase", glm::vec3(0, 0, 0), glm::vec3(116.0 / 255, 100.0 / 255, 78.0 / 255), tankSize);
    // AddMeshToList(firstBase);
    // Mesh* secondBase = object2D::CreateTankSecondBase("secondBase", glm::vec3(0, 0, 0), glm::vec3(204.0 / 255, 175.0 / 255, 136.0 / 255), tankSize);
    // AddMeshToList(secondBase);
    // Mesh* top = object2D::CreateTankTop("top", glm::vec3(0, 0, 0), glm::vec3(204.0 / 255, 175.0 / 255, 136.0 / 255), 2.5 * tankSize);
    // AddMeshToList(top);
    // Mesh *turret = object2D::CreateCeva("turret", glm::vec3(0, 0, 0), 5, glm::vec3(0, 0, 0), true);
    // AddMeshToList(turret);
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
    //
    firstTank.updateTank(height_map);

    for (auto drawable : firstTank.getParts()) {
        RenderMesh2D(drawable->getMesh(), shaders["VertexColor"], drawable->getModelMatrix());
    }
    
    if (fired_proj) {
        // std::cout << "Am tras";
        // std::cout.flush();
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(proj_pos.x, proj_pos.y);
        // modelMatrix *= transform2D::Translate(300, 500);
        RenderMesh2D(meshes["proj"], shaders["VertexColor"], modelMatrix);
        proj_pos.x += proj_vec.x * deltaTimeSeconds; 
        proj_pos.y += proj_vec.y * deltaTimeSeconds; 
        proj_vec.y -= 1000 * deltaTimeSeconds; 
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
    glm::ivec2 resolution = window->GetResolution();
    float speed = 200;
    if (window->KeyHold(GLFW_KEY_A)) {
        firstTank.changeTankX(-speed * deltaTime);
    }
    if (window->KeyHold(GLFW_KEY_D)) {
        firstTank.changeTankX(speed * deltaTime);
    }
    if (window->KeyHold(GLFW_KEY_W)) {
        firstTank.changeTurretAngle(2 * deltaTime);
        // turretAngle += 1 * deltaTime;
        // if (turretAngle > 3.14) {
        //     turretAngle = 3.14;
        // }
    }
    if (window->KeyHold(GLFW_KEY_S)) {
        firstTank.changeTurretAngle(-2 * deltaTime);
        // turretAngle -= 1 * deltaTime;
        // if (turretAngle < 0) {
        //     turretAngle = 0;
        // }
    }
    if (window->KeyHold(GLFW_KEY_SPACE)) {
        fired_proj = true;
        proj_pos = glm::vec2(tankX, tankY + 35);
        proj_vec = glm::vec2(glm::cos(angle + turretAngle) * 600, glm::sin(angle + turretAngle) * 600);
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
