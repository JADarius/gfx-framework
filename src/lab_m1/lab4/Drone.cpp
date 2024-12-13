#include "Drone.h"
#include <iostream>

using namespace std;

Drone::Drone(glm::vec3 position) {
	this->position = position;
	rotationAngle = 0.0f;
	rotationAngleBlades = 0.0f;

	// Body frame creation
	vector<VertexFormat> vertices = {
		VertexFormat(glm::vec3(-0.8, 0.1, 0.1), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
		VertexFormat(glm::vec3(-0.8, 0.1, -0.1), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
		VertexFormat(glm::vec3(0.8, 0.1, -0.1), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
		VertexFormat(glm::vec3(0.8, 0.1, 0.1), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
		VertexFormat(glm::vec3(-0.8, -0.1, 0.1), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
		VertexFormat(glm::vec3(-0.8, -0.1, -0.1), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
		VertexFormat(glm::vec3(0.8, -0.1, -0.1), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
		VertexFormat(glm::vec3(0.8, -0.1, 0.1), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
	};

	vector<unsigned int> indices = {
		0, 1, 3,
		1, 2, 3,
		4, 5, 7,
		5, 6, 7,
		0, 4, 1,
		1, 4, 5,
		2, 3, 7,
		2, 7, 6,
		0, 3, 7,
		0, 7, 4,
		1, 2, 6,
		1, 6, 5
	};

	Mesh* mesh = new Mesh("body frame");
	mesh->InitFromData(vertices, indices);

	meshes.push_back(mesh);

	Drawable* body_frame1 = new Drawable(mesh);
	body.push_back(body_frame1);
	Drawable* body_frame2 = new Drawable(mesh);
	glm::mat4 modelMatrix = glm::mat4(1);
	body_frame2->setModelMatrix(modelMatrix);
	body.push_back(body_frame2);

	// Cubes creation
	vector<VertexFormat> vertices_cube = {
		VertexFormat(glm::vec3(-0.1, -0.1, 0.1), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
		VertexFormat(glm::vec3(-0.1, -0.1, -0.1), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
		VertexFormat(glm::vec3(-0.1, 0.1, 0.1), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
		VertexFormat(glm::vec3(-0.1, 0.1, -0.1), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
		VertexFormat(glm::vec3(0.1, -0.1, 0.1), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
		VertexFormat(glm::vec3(0.1, -0.1, -0.1), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
		VertexFormat(glm::vec3(0.1, 0.1, 0.1), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
		VertexFormat(glm::vec3(0.1, 0.1, -0.1), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
	};

	vector<unsigned int> indices_cube = {
		0, 1, 2,
		1, 2, 3,
		4, 6, 5,
		5, 6, 7,
		0, 2, 4,
		2, 6, 4,
		1, 5, 3,
		5, 7, 3,
		6, 2, 3,
		6, 3, 7
	};

	Mesh* cube = new Mesh("cube");
	cube->InitFromData(vertices_cube, indices_cube);

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
	vector<VertexFormat> vertices_blade = {
		VertexFormat(glm::vec3(-0.8, 0.1, 0.1), glm::vec3(0, 1, 0), glm::vec3(0, 0, 0)),
		VertexFormat(glm::vec3(-0.8, 0.1, -0.1), glm::vec3(0, 1, 0), glm::vec3(0, 0, 0)),
		VertexFormat(glm::vec3(0.8, 0.1, -0.1), glm::vec3(0, 1, 0), glm::vec3(0, 0, 0)),
		VertexFormat(glm::vec3(0.8, 0.1, 0.1), glm::vec3(0, 1, 0), glm::vec3(0, 0, 0)),
		VertexFormat(glm::vec3(-0.8, -0.1, 0.1), glm::vec3(0, 1, 0), glm::vec3(0, 0, 0)),
		VertexFormat(glm::vec3(-0.8, -0.1, -0.1), glm::vec3(0, 1, 0), glm::vec3(0, 0, 0)),
		VertexFormat(glm::vec3(0.8, -0.1, -0.1), glm::vec3(0, 1, 0), glm::vec3(0, 0, 0)),
		VertexFormat(glm::vec3(0.8, -0.1, 0.1), glm::vec3(0, 1, 0), glm::vec3(0, 0, 0)),
	};

	vector<unsigned int> indices_blade = {
		0, 1, 3,
		1, 2, 3,
		4, 5, 7,
		5, 6, 7,
		0, 4, 1,
		1, 4, 5,
		2, 3, 7,
		2, 7, 6,
		0, 3, 7,
		0, 7, 4,
		1, 2, 6,
		1, 6, 5
	};

	Mesh* blade = new Mesh("blade");
	blade->InitFromData(vertices_blade, indices_blade);

	meshes.push_back(blade);

	Drawable* first_blade = new Drawable(blade);
	body.push_back(first_blade);

	Drawable* second_blade = new Drawable(blade);
	body.push_back(second_blade);

	Drawable* third_blade = new Drawable(blade);
	body.push_back(third_blade);

	Drawable* fourth_blade = new Drawable(blade);
	body.push_back(fourth_blade);
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
	position.x -= diff;
}

void Drone::updatePosY(float diff) {
	position.y -= diff;
}

void Drone::updatePosZ(float diff) {
	position.z -= diff;
}

void printMatrix(const glm::mat4& matrix) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			std::cout << matrix[i][j] << " ";
		}
		std::cout << '\n';
	}
}

void Drone::updateBody(float deltaTime) {
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

}

void Drone::rotate(float diff) {
	rotationAngle -= diff;
}

float Drone::getRotation() {
	return rotationAngle;
}
