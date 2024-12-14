#pragma once

#include "core/gpu/mesh.h"
#include "core/engine.h"
#include "utils/gl_utils.h"
#include "Drawable.h"
#include "Hitbox.h"
#include "object3D.h"

class Tree
{
public:
	Tree(glm::vec3 position);
	~Tree();
	std::vector<Drawable*> getBody();
	std::vector<Hitbox*> getHitboxes();
	float getPosX();
	float getPosY();
	float getPosZ();
	glm::vec3 getPos();
private:
	std::vector<Drawable*> body;
	std::vector<Mesh*> meshes;
	glm::vec3 position;
	std::vector<Hitbox*> hitboxes;
};
