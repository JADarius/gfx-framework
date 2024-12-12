#pragma once

#include "core/gpu/mesh.h"
#include "core/engine.h"
#include "utils/gl_utils.h"

class Drone
{
public:
	Drone(glm::vec3 position);
	~Drone();
	Mesh* getBody();
	float getPosX();
	float getPosY();
	float getPosZ();
	void updatePosX(float diff);
	void updatePosY(float diff);
	void updatePosZ(float diff);
	glm::vec3 getPos();
private:
	Mesh* body;
	glm::vec3 position;
};
