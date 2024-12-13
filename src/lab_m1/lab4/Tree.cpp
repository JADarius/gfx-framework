#include "Tree.h"
#include <iostream>

using namespace std;

Tree::Tree(glm::vec3 position) {
	this->position = position;

	Mesh* base = object3D::createCylinder(glm::vec3(0, 0, 0), glm::vec3(66.0f/255, 21.0f/255, 10.0f/255), 0.1, 0.8);
	meshes.push_back(base);

	Drawable* wood = new Drawable(base);

	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, position - glm::vec3(0, 0.145, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 0.8, 1));
	wood->setModelMatrix(modelMatrix);

	body.push_back(wood);

	Mesh* cone = object3D::createCone(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), 0.5, 0.6);
	meshes.push_back(cone);

	Drawable* firstLeaves = new Drawable(cone);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, position + glm::vec3(0, 0.5, 0));
	firstLeaves->setModelMatrix(modelMatrix);

	body.push_back(firstLeaves);

	Drawable* secondLeaves = new Drawable(cone);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, position + glm::vec3(0, 0.8, 0));
	secondLeaves->setModelMatrix(modelMatrix);

	body.push_back(secondLeaves);
}

Tree::~Tree() {}

std::vector<Drawable*> Tree::getBody() {
	return body;
}

float Tree::getPosX() {
	return position.x;
}

float Tree::getPosY() {
	return position.y;
}

float Tree::getPosZ() {
	return position.z;
}

glm::vec3 Tree::getPos() {
	return position;
}

