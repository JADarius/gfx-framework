#include "Tree.h"
#include <iostream>

using namespace std;

Tree::Tree(glm::vec3 position) {
	this->position = position;

	Mesh* base = object3D::createCylinder(glm::vec3(0, 0, 0), glm::vec3(66.0f/255, 21.0f/255, 10.0f/255), 0.1, 0.8);
	meshes.push_back(base);

	Drawable* wood = new Drawable(base);

	glm::vec3 wood_center_position = position - glm::vec3(0, 0.145, 0);
	float wood_height = 0.8 * 3.0f;
	float wood_radius = 0.3f;

	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, wood_center_position);
	modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 0.8, 1) * 3.0f);
	wood->setModelMatrix(modelMatrix);

	Hitbox* wood_hitbox = new Hitbox(wood_center_position.x - wood_radius, wood_center_position.x + wood_radius, wood_center_position.y - wood_height / 2, wood_center_position.y + wood_height / 2, wood_center_position.z - wood_radius, wood_center_position.z + wood_radius);
	hitboxes.push_back(wood_hitbox);

	body.push_back(wood);

	Mesh* cone = object3D::createCone(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), 0.5, 0.6);
	meshes.push_back(cone);

	float cone_height = 0.8 * 3.0f;
	float cone_radius = 1.5f;

	Drawable* firstLeaves = new Drawable(cone);

	glm::vec3 first_cone_position = position + glm::vec3(0, 1.75, 0);

	Hitbox* first_cone_hitbox = new Hitbox(first_cone_position.x - cone_radius, first_cone_position.x + cone_radius, first_cone_position.y - cone_radius / 2, first_cone_position.y + cone_radius / 2, first_cone_position.z - cone_radius, first_cone_position.z + cone_radius);
	hitboxes.push_back(first_cone_hitbox);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, first_cone_position);
	modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 1, 1) * 3.0f);
	firstLeaves->setModelMatrix(modelMatrix);

	body.push_back(firstLeaves);

	Drawable* secondLeaves = new Drawable(cone);

	glm::vec3 second_cone_position = position + glm::vec3(0, 2.75, 0);

	Hitbox* second_cone_hitbox = new Hitbox(second_cone_position.x - cone_radius, second_cone_position.x + cone_radius, second_cone_position.y - cone_radius / 2, second_cone_position.y + cone_radius / 2, second_cone_position.z - cone_radius, second_cone_position.z + cone_radius);
	hitboxes.push_back(second_cone_hitbox);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, second_cone_position);
	modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 1, 1) * 3.0f);
	secondLeaves->setModelMatrix(modelMatrix);

	body.push_back(secondLeaves);
}

Tree::~Tree() {}

std::vector<Drawable*> Tree::getBody() {
	return body;
}

std::vector<Hitbox*> Tree::getHitboxes() {
	return hitboxes;
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

