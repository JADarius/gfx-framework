#include "lab_m1/tema1/projectile.h"
#include "lab_m1/tema1/drawable.h"
#include "lab_m1/tema1/transform2D.h"
#include "lab_m1/tema1/object2D.h"

const int THRESHOLD = 1;

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
    float distance = glm::sqrt((tankX - proj_pos.x) * (tankX - proj_pos.x) + (tankY - proj_pos.y) * (tankY - proj_pos.y));
    return distance <= 6.5 * tankSize;
}

bool Projectile::checkCollisionField(std::vector<float> &height_map) {
    float Ax = glm::floor(proj_pos.x / 10) * 10; 
    float Bx = glm::ceil(proj_pos.x / 10) * 10; 
    float Ay = height_map[Ax / 10];
    float By = height_map[Bx / 10];
    float t = (proj_pos.x - Ax) / (Bx - Ax);
    float ground_proj_y = Ay + t * (By - Ay);
    return proj_pos.y - ground_proj_y  < THRESHOLD;
}

bool Projectile::isEnabled() {
    return enabled;
}

void Projectile::disable() {
    enabled = false;
}

float Projectile::getProjX() {
    return proj_pos.x;
}

float Projectile::getProjY() {
    return proj_pos.y;
}
