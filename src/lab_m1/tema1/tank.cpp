#include "lab_m1/tema1/tank.h"
#include "lab_m1/tema1/drawable.h"
#include "lab_m1/tema1/object2D.h"
#include "lab_m1/tema1/transform2D.h"

int firstBaseIndex = 0;
int secondBaseIndex = 1;
int topIndex = 2;
int turretIndex = 3;
int projIndex = 4;

Tank::Tank(float tankX, float tankSize, float turretAngle) {
    this->tankX = tankX;
    this->tankSize = tankSize;
    this->turretAngle = turretAngle;
    parts = std::vector<Drawable*>();

    Mesh* firstBase = object2D::CreateTankFirstBase("firstBase", glm::vec3(0, 0, 0), glm::vec3(116.0 / 255, 100.0 / 255, 78.0 / 255), tankSize);
    parts.push_back(new Drawable(firstBase)); 
    Mesh* secondBase = object2D::CreateTankSecondBase("secondBase", glm::vec3(0, 0, 0), glm::vec3(204.0 / 255, 175.0 / 255, 136.0 / 255), tankSize);
    parts.push_back(new Drawable(secondBase)); 
    Mesh* top = object2D::CreateTankTop("top", glm::vec3(0, 0, 0), glm::vec3(204.0 / 255, 175.0 / 255, 136.0 / 255), 2.5 * tankSize);
    parts.push_back(new Drawable(top)); 
    Mesh *turret = object2D::CreateCeva("turret", glm::vec3(0, 0, 0), 5, glm::vec3(0, 0, 0), true);
    parts.push_back(new Drawable(turret)); 
}

Tank::~Tank() {
}

void Tank::updateTank(std::vector<float> &height_map) {
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
}

std::vector<Drawable*> Tank::getParts() {
    return parts;
}

void Tank::changeTankX(float delta) {
    tankX += delta;
}

void Tank::changeTurretAngle(float delta) {
    turretAngle += delta;
}

float Tank::getTankX() {
    return tankX;
}
