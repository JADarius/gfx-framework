#pragma once

#include "core/gpu/mesh.h"
#include "core/engine.h"
#include "utils/gl_utils.h"

class Field
{
public:
	Field(int n, int m);
	~Field();
	Mesh* getBody();
private:
	Mesh* body;
};
