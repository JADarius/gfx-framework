#include "lab_m1/tema1/projectile.h"
#include "lab_m1/tema1/drawable.h"
#include "lab_m1/tema1/transform2D.h"
#include "lab_m1/tema1/object2D.h"
#include <iostream>

Projectile::Projectile(glm::vec2 proj_vec, glm::vec2 proj_pos) : proj_vec(proj_vec), proj_pos(proj_pos) {
    Mesh* proj = object2D::CreateProj("proj", glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 5);
    body = new Drawable(proj);
    enabled = true;
}

Projectile::~Projectile() {}

void Projectile::update(float deltaTime) {
    glm::mat3 modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(proj_pos.x, proj_pos.y);
    body->setModelMatrix(modelMatrix);
    proj_pos += proj_vec * deltaTime;
    proj_vec.y -= 1000 * deltaTime; 
}

Drawable* Projectile::getBody() {
    return body;
}

bool Projectile::checkCollisionTank(float tankX, float tankY, float tankSize) {
    return (proj_pos.x >= tankX - 6.5 * tankSize &&
            proj_pos.x <= tankX + 6.5 * tankSize) &&
           (proj_pos.y >= tankY && proj_pos.y <= tankY + 2.5 * tankSize);
}

bool Projectile::isEnabled() {
    return enabled;
}

void Projectile::disable() {
    enabled = false;
}
