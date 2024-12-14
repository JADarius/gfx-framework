#include "lab_m1/lab4/lab4.h"

#include <vector>
#include <string>
#include <iostream>
#include <ctime>
#include <cstdlib>


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

std::vector<Tree*> genTrees() {
    std::vector<Tree*> treeList;
    srand(time(NULL));
    for (int count = 0; count < 20; count++) {
        GENERATE:
        int x = rand() % 50;
        int z = rand() % 50;
        bool valid = true;
        for (auto tree : treeList) {
            if (abs(tree->getPosX() - x) < 5.0 && abs(tree->getPosZ() - z) < 5.0) {
                valid = false;
            }
            if (x < 5.0 || z < 5.0 || x > 45.0 || z > 45.0) {
                valid = false;
            }
        }
        if (valid) {
            Tree* tree = new Tree(glm::vec3(x, 1, z));
            treeList.push_back(tree);
        }
        else {
            goto GENERATE;
        }
    }
    return treeList;
}


void Lab4::Init()
{
    // Create a shader program for drawing face polygon with the color of the normal
    {
        Shader *shader = new Shader("HwShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab4", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab4", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    polygonMode = GL_FILL;

    Mesh* mesh = new Mesh("box");
    mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
    meshes[mesh->GetMeshID()] = mesh;

    // Sets the resolution of the small viewport
    glm::ivec2 resolution = window->GetResolution();
    miniViewportArea = ViewportArea(50, 50, resolution.x / 5.f, resolution.y / 5.f);

    field = new Field(50, 50);

    drone = new Drone(glm::vec3(25, 5, 25));

    treeList = genTrees();

    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
}

void Lab4::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(146.0 / 255, 179.0 / 255, 232.0 / 255, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Lab4::RenderScene() {
    RenderSimpleMesh(field->getBody(), shaders["HwShader"], glm::mat4(1));

    //modelMatrix = glm::mat4(1);
    //modelMatrix = glm::translate(modelMatrix, drone->getPos());
    //modelMatrix = glm::rotate(modelMatrix, rotationAngle + glm::radians(45.0f), glm::vec3(0, 1, 0));
    for (auto drawable : drone->getBody()) {
        RenderMesh(drawable->getMesh(), shaders["VertexNormal"], drawable->getModelMatrix());
    }
    for (Tree* tree : treeList) {
		for (auto drawable : tree->getBody()) {
			RenderMesh(drawable->getMesh(), shaders["VertexNormal"], drawable->getModelMatrix());
		}
    }
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(10.0f, 10.0f, 10.0f));
	RenderMesh(meshes["tree"], shaders["VertexNormal"], glm::mat4(1));
}

void Lab4::RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix)
{
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(drone->getCamera()->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
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
    float moveSpeed = 10.0;
    float rotationSpeed = 2.0;
    glm::vec3 previous_pos = drone->getPos();
    // TODO(student): Add transformation logic
    if (window->KeyHold(GLFW_KEY_A)) {
        drone->updatePosZ(-deltaTime * moveSpeed * glm::sin(drone->getRotation()));
		drone->updatePosX(deltaTime * moveSpeed * glm::cos(drone->getRotation()));
    }
    if (window->KeyHold(GLFW_KEY_D)) {
        drone->updatePosZ(deltaTime * moveSpeed * glm::sin(drone->getRotation()));
		drone->updatePosX(-deltaTime * moveSpeed * glm::cos(drone->getRotation()));
    }
    if (window->KeyHold(GLFW_KEY_W)) {
        drone->updatePosZ(deltaTime * moveSpeed * glm::cos(drone->getRotation()));
		drone->updatePosX(deltaTime * moveSpeed * glm::sin(drone->getRotation()));
    }
    if (window->KeyHold(GLFW_KEY_S)) {
        drone->updatePosZ(-deltaTime * moveSpeed * glm::cos(drone->getRotation()));
		drone->updatePosX(-deltaTime * moveSpeed * glm::sin(drone->getRotation()));
    }
    if (window->KeyHold(GLFW_KEY_R)) drone->updatePosY(-deltaTime * moveSpeed);
    if (window->KeyHold(GLFW_KEY_F)) drone->updatePosY(deltaTime * moveSpeed);
    if (window->KeyHold(GLFW_KEY_Q)) drone->rotate(deltaTime * rotationSpeed);
    if (window->KeyHold(GLFW_KEY_E)) drone->rotate(-deltaTime * rotationSpeed);
    for (auto tree : treeList) {
        for (auto hitbox : tree->getHitboxes()) {
            float x = max(hitbox->getXMin(), min(hitbox->getXMax(), drone->getPosX()));
            float y = max(hitbox->getYMin(), min(hitbox->getYMax(), drone->getPosY()));
            float z = max(hitbox->getZMin(), min(hitbox->getZMax(), drone->getPosZ()));

            float distance = glm::sqrt((x - drone->getPosX()) * (x - drone->getPosX()) + (y - drone->getPosY()) * (y - drone->getPosY()) + (z - drone->getPosZ()) * (z - drone->getPosZ()));

            // Collision detected
            if (distance < 0.5f) {
                drone->setPos(previous_pos);
            }
        }
    }
}

void Lab4::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    // Bind model matrix
    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Bind view matrix
    glm::mat4 viewMatrix = drone->getCamera()->GetViewMatrix();
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Bind projection matrix
    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
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
