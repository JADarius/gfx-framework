#include "lab_m1/lab4/lab4.h"

#include <vector>
#include <string>
#include <iostream>

#include "lab_m1/lab4/transform3D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab4::Lab4()
{
}


Lab4::~Lab4()
{
    delete field;
    delete drone;
}


void Lab4::Init()
{
    polygonMode = GL_FILL;

    Mesh* mesh = new Mesh("box");
    mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
    meshes[mesh->GetMeshID()] = mesh;

    // Initialize tx, ty and tz (the translation steps)
    translateX = 0;
    translateY = 0;
    translateZ = 0;

    // Initialize sx, sy and sz (the scale factors)
    scaleX = 1;
    scaleY = 1;
    scaleZ = 1;

    // Initialize angular steps
    angularStepOX = 0;
    rotationAngle = 0;
    angularStepOZ = 0;

    // Sets the resolution of the small viewport
    glm::ivec2 resolution = window->GetResolution();
    miniViewportArea = ViewportArea(50, 50, resolution.x / 5.f, resolution.y / 5.f);

    field = new Field(100, 100);

    drone = new Drone(glm::vec3(0, 0, 0));
}

void Lab4::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(146.0 / 255, 179.0 / 255, 232.0 / 255, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Lab4::RenderScene() {
    //RenderMesh(field->getBody(), shaders["VertexNormal"], glm::mat4(1));

    //modelMatrix = glm::mat4(1);
    //modelMatrix = glm::translate(modelMatrix, drone->getPos());
    //modelMatrix = glm::rotate(modelMatrix, rotationAngle + glm::radians(45.0f), glm::vec3(0, 1, 0));
    for (auto drawable : drone->getBody()) {
        RenderMesh(drawable->getMesh(), shaders["VertexNormal"], drawable->getModelMatrix());
    }
}

void Lab4::Update(float deltaTimeSeconds)
{
    glLineWidth(3);
    glPointSize(5);
    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

    // Sets the screen area where to draw
    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);

    drone->updateBody(deltaTimeSeconds);

    RenderScene();
    // DrawCoordinateSystem();

    glClear(GL_DEPTH_BUFFER_BIT);
    //glViewport(miniViewportArea.x, miniViewportArea.y, miniViewportArea.width, miniViewportArea.height);

    // TODO(student): render the scene again, in the new viewport
    //DrawCoordinateSystem();
}

void Lab4::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab4::OnInputUpdate(float deltaTime, int mods)
{
    float speed = 2.0;
    // TODO(student): Add transformation logic
    if (window->KeyHold(GLFW_KEY_A)) {
        drone->updatePosZ(deltaTime * speed * glm::sin(drone->getRotation()));
		drone->updatePosX(deltaTime * speed * glm::cos(drone->getRotation()));
    }
    if (window->KeyHold(GLFW_KEY_D)) {
        drone->updatePosZ(-deltaTime * speed * glm::sin(drone->getRotation()));
		drone->updatePosX(-deltaTime * speed * glm::cos(drone->getRotation()));
    }
    if (window->KeyHold(GLFW_KEY_W)) {
        drone->updatePosZ(deltaTime * speed * glm::cos(drone->getRotation()));
		drone->updatePosX(deltaTime * speed * glm::sin(drone->getRotation()));
    }
    if (window->KeyHold(GLFW_KEY_S)) {
        drone->updatePosZ(-deltaTime * speed * glm::cos(drone->getRotation()));
		drone->updatePosX(-deltaTime * speed * glm::sin(drone->getRotation()));
    }
    if (window->KeyHold(GLFW_KEY_R)) drone->updatePosY(-deltaTime * speed);
    if (window->KeyHold(GLFW_KEY_F)) drone->updatePosY(deltaTime * speed);
    if (window->KeyHold(GLFW_KEY_Q)) drone->rotate(deltaTime * speed);
    if (window->KeyHold(GLFW_KEY_E)) drone->rotate(-deltaTime * speed);
}


void Lab4::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_SPACE)
    {
        switch (polygonMode)
        {
        case GL_POINT:
            polygonMode = GL_FILL;
            break;
        case GL_LINE:
            polygonMode = GL_POINT;
            break;
        default:
            polygonMode = GL_LINE;
            break;
        }
    }
    
    // TODO(student): Add viewport movement and scaling logic
}


void Lab4::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab4::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Lab4::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab4::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab4::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Lab4::OnWindowResize(int width, int height)
{
}
