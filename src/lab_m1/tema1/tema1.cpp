#include "lab_m1/tema1/tema1.h"

#include <algorithm>
#include <cmath>
#include <vector>
#include <iostream>

#include "glm/ext/scalar_constants.hpp"
#include "glm/fwd.hpp"
#include "lab_m1/tema1/drawable.h"
#include "lab_m1/tema1/transform2D.h"
#include "lab_m1/tema1/object2D.h"
#include "utils/gl_utils.h"
#include "lab_m1/tema1/projectile.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */

const float THRESHOLD = 10;
const float EPSILON = 10;
const float BLAST_RADIUS = 50;

std::vector<float> gen_heights(int length) {
    std::vector<float> height_map(length);
    for (int x = 0; x < length; x++) {
        height_map[x] = 50 * glm::sin(0.1 * x) + 50 * glm::sin(0.2 * x) + 350;
    }
    return height_map;
}

Tema1::Tema1() : firstTank(Tank(200.1, 5, 0, glm::vec3(0, 0, 1))), secondTank(Tank(1000.1, 5, 3.14, glm::vec3(1, 0, 0)))
{
    glm::ivec2 resolution = window->GetResolution();
    height_map = gen_heights(resolution.x / 10 + 1);
    projectiles = std::vector<Projectile>();
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


    // projectiles
    for (auto &proj : projectiles) {
        if (!proj.isEnabled()) {
            continue;
        }
        proj.update(deltaTimeSeconds);
        if (proj.checkCollisionTank(firstTank.getTankX(), firstTank.getTankY(), firstTank.getTankSize())) {
            firstTank.hit();
            proj.disable();
            continue;
        }
        if (proj.checkCollisionTank(secondTank.getTankX(), firstTank.getTankY(), firstTank.getTankSize())) {
            secondTank.hit();
            proj.disable();
            continue;
        }
        if (proj.checkCollisionField(height_map)) {
            std::cout.flush();
            float projX = proj.getProjX() / 10;
            float projY = proj.getProjY();
            for (int index = glm::floor(projX) - BLAST_RADIUS / 10; index <= glm::floor(projX) + BLAST_RADIUS / 10; index++) {
                float x = index * 10;
                float new_y = projY - glm::sqrt(BLAST_RADIUS * BLAST_RADIUS - (x - projX * 10) * (x - projX * 10));
                height_map[index] = std::min(height_map[index], new_y);
            }
            proj.disable();
            continue;
        }
        Drawable* body = proj.getBody();
        RenderMesh2D(body->getMesh(), shaders["VertexColor"], body->getModelMatrix());
    }

    // Field
    // Check for big differences
    for (int index = 0; index < height_map.size() - 1; index++) {
        if (height_map[index + 1] - height_map[index] > THRESHOLD) {
            height_map[index + 1] -= EPSILON * deltaTimeSeconds;
            height_map[index] += EPSILON * deltaTimeSeconds;
        }
        if (height_map[index] - height_map[index + 1] > THRESHOLD) {
            height_map[index + 1] += EPSILON * deltaTimeSeconds;
            height_map[index] -= EPSILON * deltaTimeSeconds;
        }
    }
    
    for (int index = 0; index < height_map.size() - 1; index++) {
        modelMatrix = glm::mat3(1); 
        modelMatrix *= transform2D::Translate((index) * 10, height_map[index]);
        modelMatrix *= transform2D::Shear(index * 10, height_map[index], (index + 1) * 10, height_map[index + 1]);
        modelMatrix *= transform2D::Scale(10, std::max(height_map[index], height_map[index + 1]));
        RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);
    }


    // Tanks
    if (firstTank.isAlive()) {
        firstTank.updateTank(height_map, deltaTimeSeconds);

        for (auto drawable : firstTank.getParts()) {
            RenderMesh2D(drawable->getMesh(), shaders["VertexColor"], drawable->getModelMatrix());
        }
    }

    if (secondTank.isAlive()) {
        secondTank.updateTank(height_map, deltaTimeSeconds);

        for (auto drawable : secondTank.getParts()) {
            RenderMesh2D(drawable->getMesh(), shaders["VertexColor"], drawable->getModelMatrix());
        }
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
    }
    if (window->KeyHold(GLFW_KEY_S)) {
        firstTank.changeTurretAngle(-2 * deltaTime);
    }
    if (window->KeyHold(GLFW_KEY_LEFT)) {
        secondTank.changeTankX(-speed * deltaTime);
    }
    if (window->KeyHold(GLFW_KEY_RIGHT)) {
        secondTank.changeTankX(speed * deltaTime);
    }
    if (window->KeyHold(GLFW_KEY_UP)) {
        secondTank.changeTurretAngle(2 * deltaTime);
    }
    if (window->KeyHold(GLFW_KEY_DOWN)) {
        secondTank.changeTurretAngle(-2 * deltaTime);
    }
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_SPACE && firstTank.isAlive()) {
        projectiles.push_back(firstTank.fireProj());
    }
    if (key == GLFW_KEY_ENTER && secondTank.isAlive()) {
        projectiles.push_back(secondTank.fireProj());
    }
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
