#include "Drone.h"

using namespace std;

Drone::Drone(glm::vec3 position) {
	this->position = position;

	vector<VertexFormat> vertices = {
		VertexFormat(glm::vec3(-0.5, 0.1, 0.1), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
		VertexFormat(glm::vec3(-0.5, 0.1, -0.1), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
		VertexFormat(glm::vec3(-0.1, 0.1, -0.5), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
		VertexFormat(glm::vec3(0.1, 0.1, -0.5), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
		VertexFormat(glm::vec3(0.5, 0.1, -0.1), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
		VertexFormat(glm::vec3(0.5, 0.1, 0.1), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
		VertexFormat(glm::vec3(0.1, 0.1, 0.5), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
		VertexFormat(glm::vec3(-0.1, 0.1, 0.5), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
		VertexFormat(glm::vec3(-0.5, -0.1, 0.1), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
		VertexFormat(glm::vec3(-0.5, -0.1, -0.1), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
		VertexFormat(glm::vec3(-0.1, -0.1, -0.5), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
		VertexFormat(glm::vec3(0.1, -0.1, -0.5), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
		VertexFormat(glm::vec3(0.5, -0.1, -0.1), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
		VertexFormat(glm::vec3(0.5, -0.1, 0.1), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
		VertexFormat(glm::vec3(0.1, -0.1, 0.5), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
		VertexFormat(glm::vec3(-0.1, -0.1, 0.5), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
	};

	vector<unsigned int> indices = {
		0, 1, 5,
		1, 4, 5,
		2, 6, 7,
		2, 3, 6,
		8, 9, 13,
		9, 12, 13,
		10, 14, 15,
		10, 11, 14,
		9, 1, 0,
		9, 0, 8,
		2, 3, 11,
		2, 11, 10,
		4, 5, 12,
		5, 12, 13,
		7, 6, 14,
		7, 14, 15,
		0, 5, 13,
		0, 13, 8,
		1, 4, 12,
		1, 12, 9,
		2, 7, 15,
		2, 15, 10,
		3, 6, 14,
		3, 14, 11
	};

	body = new Mesh("Frame");
	body->InitFromData(vertices, indices);
}

Drone::~Drone() {}

Mesh* Drone::getBody() {
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

void Drone::updatePosX(float diff) {
	position.x -= diff;
}

void Drone::updatePosY(float diff) {
	position.y -= diff;
}

void Drone::updatePosZ(float diff) {
	position.z -= diff;
}
