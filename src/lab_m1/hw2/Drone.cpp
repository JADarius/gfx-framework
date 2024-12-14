#include "Drone.h"
#include <iostream>

using namespace std;

Drone::Drone(glm::vec3 position) {
	this->position = position;
	rotationAngle = 0.0f;
	rotationAngleBlades = 0.0f;

	camera = new Camera(position, position, glm::vec3(0, 1, 0));

	// Body frame creation
	Mesh* frame = object3D::createRectCuboid(glm::vec3(0, 0, 0), glm::vec3(0.5f, 0.5f, 0.5f), 0.8, 0.1, 0.1);

	meshes.push_back(frame);

	Drawable* body_frame1 = new Drawable(frame);
	body.push_back(body_frame1);
	Drawable* body_frame2 = new Drawable(frame);
	glm::mat4 modelMatrix = glm::mat4(1);
	body_frame2->setModelMatrix(modelMatrix);
	body.push_back(body_frame2);

	// Cubes creation
	Mesh* cube = object3D::createCube(glm::vec3(0, 0, 0), glm::vec3(0.5, 0.5, 0.5), 0.1);

	meshes.push_back(cube);

	Drawable* first_cube = new Drawable(cube);
	body.push_back(first_cube);

	Drawable* second_cube = new Drawable(cube);
	body.push_back(second_cube);

	Drawable* third_cube = new Drawable(cube);
	body.push_back(third_cube);

	Drawable* fourth_cube = new Drawable(cube);
	body.push_back(fourth_cube);

	// Blades creation
	Mesh* blade = object3D::createRectCuboid(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 0.8, 0.1, 0.1);

	meshes.push_back(blade);

	Drawable* first_blade = new Drawable(blade);
	body.push_back(first_blade);

	Drawable* second_blade = new Drawable(blade);
	body.push_back(second_blade);

	Drawable* third_blade = new Drawable(blade);
	body.push_back(third_blade);

	Drawable* fourth_blade = new Drawable(blade);
	body.push_back(fourth_blade);

	Mesh* package_mesh = object3D::createCube(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), 0.2);
	meshes.push_back(package_mesh);

	package = new Drawable(package_mesh);

	// Arrow creation
	main_part = new Drawable(blade);
	body.push_back(main_part);
	left_part = new Drawable(blade);
	body.push_back(left_part);
	right_part = new Drawable(blade);
	body.push_back(right_part);
}

Drone::~Drone() {}

std::vector<Drawable*> Drone::getBody() {
	return body;
}

float Drone::getPosX() {
	return position.x;
}

float Drone::getPosY() {
	return position.y;
}

float Drone::getPosZ() {
	return position.z;
}

glm::vec3 Drone::getPos() {
	return position;
}

void Drone::updatePosX(float diff) {
	if (position.x - diff > 0.5f && position.x - diff < 45.0f) {
		position.x -= diff;
	}
}

void Drone::updatePosY(float diff) {
	if (position.y - diff > 1.0f) {
		position.y -= diff;
	}
}

void Drone::updatePosZ(float diff) {
	if (position.z - diff > 0.5f && position.z - diff < 45.0f) {
		position.z -= diff;
	}
}

void Drone::updateBody(float deltaTime, glm::vec3 destination) {
	// Body frame
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, position);
	modelMatrix = glm::rotate(modelMatrix, glm::radians(45.0f) + rotationAngle, glm::vec3(0, 1, 0));
	body[0]->setModelMatrix(modelMatrix);
	modelMatrix = glm::rotate(modelMatrix, glm::radians(90.0f), glm::vec3(0, 1, 0));
	body[1]->setModelMatrix(modelMatrix);

	// Cubes
	float angle = glm::radians(45.0f) + rotationAngle;
	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, position + glm::vec3(0.7 * glm::sin(angle), 0.2, 0.7 * glm::cos(angle)));
	modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(0, 1, 0));
	body[2]->setModelMatrix(modelMatrix);

	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, position + glm::vec3(-0.7 * glm::sin(angle), 0.2, -0.7 * glm::cos(angle)));
	modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(0, 1, 0));
	body[3]->setModelMatrix(modelMatrix);

	angle += glm::radians(90.0f);
	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, position + glm::vec3(0.7 * glm::sin(angle), 0.2, 0.7 * glm::cos(angle)));
	modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(0, 1, 0));
	body[4]->setModelMatrix(modelMatrix);

	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, position + glm::vec3(-0.7 * glm::sin(angle), 0.2, -0.7 * glm::cos(angle)));
	modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(0, 1, 0));
	body[5]->setModelMatrix(modelMatrix);

	// Blades
	rotationAngleBlades += 10 * deltaTime;
	angle = glm::radians(45.0f) + rotationAngle;

	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, position + glm::vec3(0.7 * glm::sin(angle), 0.35, 0.7 * glm::cos(angle)));
	modelMatrix = glm::rotate(modelMatrix, rotationAngleBlades, glm::vec3(0, 1, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f, 0.2f, 0.2f));
	body[6]->setModelMatrix(modelMatrix);

	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, position + glm::vec3(-0.7 * glm::sin(angle), 0.35, -0.7 * glm::cos(angle)));
	modelMatrix = glm::rotate(modelMatrix, rotationAngleBlades, glm::vec3(0, 1, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f, 0.2f, 0.2f));
	body[7]->setModelMatrix(modelMatrix);

	angle += glm::radians(90.0f);

	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, position + glm::vec3(0.7 * glm::sin(angle), 0.35, 0.7 * glm::cos(angle)));
	modelMatrix = glm::rotate(modelMatrix, rotationAngleBlades, glm::vec3(0, 1, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f, 0.2f, 0.2f));
	body[8]->setModelMatrix(modelMatrix);

	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, position + glm::vec3(-0.7 * glm::sin(angle), 0.35, -0.7 * glm::cos(angle)));
	modelMatrix = glm::rotate(modelMatrix, rotationAngleBlades, glm::vec3(0, 1, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f, 0.2f, 0.2f));
	body[9]->setModelMatrix(modelMatrix);

	// Update package
	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, position - glm::vec3(0, 0.3f, 0));
	modelMatrix = glm::rotate(modelMatrix, rotationAngle, glm::vec3(0, 1.0f, 0));
	package->setModelMatrix(modelMatrix);

	// Update camera
	glm::vec3 cameraPosition = glm::vec3(position.x + 4 * glm::sin(rotationAngle), position.y + 2, position.z + 4 * glm::cos(rotationAngle));
	camera->Set(cameraPosition, position, glm::vec3(0, 1, 0));

	// Update arrow
	glm::vec3 direction = glm::normalize(position - destination);
	float arrowRotation = glm::atan2(direction.x, direction.z);
	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, position - glm::vec3(0, position.y - 1, 0));
	modelMatrix = glm::rotate(modelMatrix, arrowRotation + glm::radians(90.0f), glm::vec3(0, 1.0f, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.96f, 1.0f, 1.0f));
	main_part->setModelMatrix(modelMatrix);
	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, position - glm::vec3(0.7 * glm::sin(arrowRotation), position.y - 1, 0.7 * glm::cos(arrowRotation)));
	modelMatrix = glm::rotate(modelMatrix, arrowRotation + glm::radians(150.0f), glm::vec3(0, 1.0f, 0));
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5, 0, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.6f, 1.0f, 1.0f));
	right_part->setModelMatrix(modelMatrix);
	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, position - glm::vec3(0.7 * glm::sin(arrowRotation), position.y - 1, 0.7 * glm::cos(arrowRotation)));
	modelMatrix = glm::rotate(modelMatrix, arrowRotation + glm::radians(30.0f), glm::vec3(0, 1.0f, 0));
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5, 0, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.6f, 1.0f, 1.0f));
	left_part->setModelMatrix(modelMatrix);
}

void Drone::rotate(float diff) {
	rotationAngle -= diff;
}

float Drone::getRotation() {
	return rotationAngle;
}

void Drone::setPos(glm::vec3 pos) {
	this->position = pos;
}

Camera* Drone::getCamera() {
	return camera;
}

void Drone::takePackage() {
	body.push_back(package);
}

void Drone::deliverPackage() {
	body.pop_back();
}
