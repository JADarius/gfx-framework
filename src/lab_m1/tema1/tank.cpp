#include "lab_m1/tema1/tank.h"
#include "lab_m1/tema1/drawable.h"
#include "lab_m1/tema1/object2D.h"
#include "lab_m1/tema1/projectile.h"
#include "lab_m1/tema1/transform2D.h"

int firstBaseIndex = 0;
int secondBaseIndex = 1;
int topIndex = 2;
int turretIndex = 3;
int healthBarIndex = 4;
int healthBarProgressIndex = 5;

Tank::Tank(float tankX, float tankSize, float turretAngle, glm::vec3 color) {
    this->tankX = tankX;
    this->tankSize = tankSize;
    this->turretAngle = turretAngle;
    fired_proj = false;
    parts = std::vector<Drawable*>();
    hitpoints = 50;

    Mesh* firstBase = object2D::CreateTankFirstBase("firstBase", glm::vec3(0, 0, 0), glm::vec3(116.0 / 255, 100.0 / 255, 78.0 / 255), tankSize);
    parts.push_back(new Drawable(firstBase)); 
    Mesh* secondBase = object2D::CreateTankSecondBase("secondBase", glm::vec3(0, 0, 0), color, tankSize);
    parts.push_back(new Drawable(secondBase)); 
    Mesh* top = object2D::CreateTankTop("top", glm::vec3(0, 0, 0), color, 2.5 * tankSize);
    parts.push_back(new Drawable(top)); 
    Mesh *turret = object2D::CreateCeva("turret", glm::vec3(0, 0, 0), 5, glm::vec3(0, 0, 0), true);
    parts.push_back(new Drawable(turret)); 
    Mesh *healthBar = object2D::CreateCeva("healthBar", glm::vec3(0, 0, 0), 1, glm::vec3(0, 0, 0), false);
    parts.push_back(new Drawable(healthBar));
    Mesh *healthBarProgress = object2D::CreateCeva("healthBarProgress", glm::vec3(0, 0, 0), 1, glm::vec3(0, 0, 0), true);
    parts.push_back(new Drawable(healthBarProgress));
}

Tank::~Tank() {
}

void Tank::updateTank(std::vector<float> &height_map, float deltaTime) {
    // Calculate Y
    float Ax = glm::floor(tankX / 10) * 10; 
    float Bx = glm::ceil(tankX / 10) * 10; 
    float Ay = height_map[Ax / 10];
    float By = height_map[Bx / 10];
    float t = (tankX - Ax) / (Bx - Ax);
    tankY = Ay + t * (By - Ay);
    // Calculate rotation
    float Vx = Bx - Ax;
    float Vy = By - Ay;
    angle = glm::atan2(Vy, Vx);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(tankX, tankY);
    modelMatrix *= transform2D::Rotate(angle);
    parts[firstBaseIndex]->setModelMatrix(modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(tankX, tankY);
    modelMatrix *= transform2D::Rotate(angle);
    modelMatrix *= transform2D::Translate(0, tankSize);
    parts[secondBaseIndex]->setModelMatrix(modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(tankX, tankY);
    modelMatrix *= transform2D::Rotate(angle);
    modelMatrix *= transform2D::Translate(0, 3 * tankSize);
    parts[topIndex]->setModelMatrix(modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(tankX, tankY);
    modelMatrix *= transform2D::Rotate(angle);
    modelMatrix *= transform2D::Translate(0, 4.5 * tankSize - 2.5);
    modelMatrix *= transform2D::Rotate(turretAngle);
    modelMatrix *= transform2D::Translate(0, 2.5);
    modelMatrix *= transform2D::Scale(1.4 * tankSize, 1);
    parts[turretIndex]->setModelMatrix(modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(tankX - 25, tankY + 70);
    modelMatrix *= transform2D::Scale(50, 10);
    parts[healthBarIndex]->setModelMatrix(modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(tankX - 25, tankY + 70);
    modelMatrix *= transform2D::Scale(hitpoints, 10);
    parts[healthBarProgressIndex]->setModelMatrix(modelMatrix);
}

std::vector<Drawable*> Tank::getParts() {
    return parts;
}

void Tank::changeTankX(float delta) {
    tankX += delta;
}

void Tank::changeTurretAngle(float delta) {
    turretAngle += delta;
    if (turretAngle > 3.14) {
        turretAngle = 3.14;
    }
    if (turretAngle < 0) {
        turretAngle = 0;
    }
}

float Tank::getTankX() {
    return tankX;
}

float Tank::getTankY() {
    return tankY;
}

float Tank::getTankSize() {
    return tankSize;
}

Projectile Tank::fireProj() {
    fired_proj = true;
    proj_pos = glm::vec2(tankX + 5 * tankSize * glm::cos(angle + turretAngle), tankY + 4 * tankSize + 5 * tankSize * glm::sin(angle + turretAngle));
    proj_vec = glm::vec2(glm::cos(angle + turretAngle) * 600, glm::sin(angle + turretAngle) * 600);
    return Projectile(proj_vec, proj_pos);
}

void Tank::hit() {
    hitpoints -= 10;
}

bool Tank::isAlive() {
    return hitpoints > 0;
}
