#include "drawable.h"

Drawable::Drawable(Mesh* mesh) : mesh(mesh), modelMatrix(glm::mat4(1)) {}

Drawable::~Drawable() {
    delete mesh;
}

glm::mat4 Drawable::getModelMatrix() {
    return modelMatrix;
}

void Drawable::setModelMatrix(glm::mat4 modelMatrix) {
    this->modelMatrix = modelMatrix;
}

Mesh* Drawable::getMesh() {
    return mesh;
}
