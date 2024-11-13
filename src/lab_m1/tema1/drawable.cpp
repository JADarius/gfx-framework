#include "drawable.h"

Drawable::Drawable(Mesh* mesh) : mesh(mesh), modelMatrix(glm::mat3(1)) {}

Drawable::~Drawable() {
    delete mesh;
}

glm::mat3 Drawable::getModelMatrix() {
    return modelMatrix;
}

void Drawable::setModelMatrix(glm::mat3 modelMatrix) {
    this->modelMatrix = modelMatrix;
}

Mesh* Drawable::getMesh() {
    return mesh;
}
