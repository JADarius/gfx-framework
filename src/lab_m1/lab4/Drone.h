#pragma once

#include "core/gpu/mesh.h"
#include "core/engine.h"
#include "utils/gl_utils.h"
#include "Drawable.h"
#include "object3D.h"
#include "Camera.h"

class Drone
{
public:
	Drone(glm::vec3 position);
	~Drone();
	std::vector<Drawable*> getBody();
	float getPosX();
	float getPosY();
	float getPosZ();
	void updatePosX(float diff);
	void updatePosY(float diff);
	void updatePosZ(float diff);
	void setPos(glm::vec3 pos);
	void rotate(float diff);
	void takePackage();
	void deliverPackage();
	Camera* getCamera();
	float getRotation();
	glm::vec3 getPos();
	void updateBody(float deltaTime);
private:
	std::vector<Drawable*> body;
	std::vector<Mesh*> meshes;
	Drawable* package;
	glm::vec3 position;
	float rotationAngle;
	float rotationAngleBlades;
	Camera* camera;
};
