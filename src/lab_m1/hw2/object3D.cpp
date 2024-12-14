#include "object3D.h"

#include <iostream>
#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


//Mesh* object2D::CreateProj(const std::string &name, glm::vec3 center, glm::vec3 color, float radius) {
//    std::vector<VertexFormat> vertices =
//    {
//        VertexFormat(center, color)
//    };
//
//    float angleUnit = glm::radians(360.0) / 36.0;
//    for (int point = 0; point <= 36; point++) {
//        vertices.push_back(
//                VertexFormat(center + glm::vec3(radius * glm::cos(point * angleUnit), radius * glm::sin(point * angleUnit), 0), color)
//                );
//    }
//
//    std::vector<unsigned int> indices;
//
//    for (int point = 1; point < 37; point++) {
//        indices.push_back(0); 
//        indices.push_back(point); 
//        indices.push_back(point + 1); 
//    }
//
//    Mesh* proj = new Mesh(name);
//
//    proj->InitFromData(vertices, indices);
//    return proj;
//}

Mesh* object3D::createCube(glm::vec3 center, glm::vec3 color, float length) {
	std::vector<VertexFormat> vertices_cube = {
		VertexFormat(center + glm::vec3(-length, -length, length), glm::vec3(0, 1, 0), color),
		VertexFormat(center + glm::vec3(-length, -length, -length), glm::vec3(0, 1, 0), color),
		VertexFormat(center + glm::vec3(-length, length, length), glm::vec3(0, 1, 0), color),
		VertexFormat(center + glm::vec3(-length, length, -length), glm::vec3(0, 1, 0), color),
		VertexFormat(center + glm::vec3(length, -length, length), glm::vec3(0, 1, 0), color),
		VertexFormat(center + glm::vec3(length, -length, -length), glm::vec3(0, 1, 0), color),
		VertexFormat(center + glm::vec3(length, length, length), glm::vec3(0, 1, 0), color),
		VertexFormat(center + glm::vec3(length, length, -length), glm::vec3(0, 1, 0), color),
	};

	std::vector<unsigned int> indices_cube = {
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

	return cube;
}

Mesh* object3D::createRectCuboid(glm::vec3 center, glm::vec3 color, float lengthOx, float lengthOy, float lengthOz) {
	std::vector<VertexFormat> vertices = {
		VertexFormat(glm::vec3(-lengthOx, lengthOy, lengthOz), glm::vec3(0, 1, 0), color),
		VertexFormat(glm::vec3(-lengthOx, lengthOy, -lengthOz), glm::vec3(0, 1, 0), color),
		VertexFormat(glm::vec3(lengthOx, lengthOy, -lengthOz), glm::vec3(0, 1, 0), color),
		VertexFormat(glm::vec3(lengthOx, lengthOy, lengthOz), glm::vec3(0, 1, 0), color),
		VertexFormat(glm::vec3(-lengthOx, -lengthOy, lengthOz), glm::vec3(0, 1, 0), color),
		VertexFormat(glm::vec3(-lengthOx, -lengthOy, -lengthOz), glm::vec3(0, 1, 0), color),
		VertexFormat(glm::vec3(lengthOx, -lengthOy, -lengthOz), glm::vec3(0, 1, 0), color),
		VertexFormat(glm::vec3(lengthOx, -lengthOy, lengthOz), glm::vec3(0, 1, 0), color),
	};

	std::vector<unsigned int> indices = {
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
	
	return mesh;
}

Mesh* object3D::createCylinder(glm::vec3 center, glm::vec3 color, float radius, float height) {
	std::vector<VertexFormat> vertices = {
		VertexFormat(center - glm::vec3(0, height / 2, 0), glm::vec3(0, 1, 0), color)
	};

    float angleUnit = glm::radians(360.0) / 36.0;
    for (int point = 0; point <= 36; point++) {
        vertices.push_back(
                VertexFormat(center + glm::vec3(radius * glm::cos(point * angleUnit), -height / 2, radius * glm::sin(point * angleUnit)), glm::vec3(0, 1, 0), color)
                );
    }
	
	vertices.push_back(VertexFormat(center + glm::vec3(0, height / 2, 0), glm::vec3(0, 1, 0), color));

    for (int point = 0; point <= 36; point++) {
        vertices.push_back(
                VertexFormat(center + glm::vec3(radius * glm::cos(point * angleUnit), height / 2, radius * glm::sin(point * angleUnit)), glm::vec3(0, 1, 0), color)
                );
    }

    std::vector<unsigned int> indices;

    for (int point = 1; point < 37; point++) {
        indices.push_back(0); 
        indices.push_back(point); 
        indices.push_back(point + 1); 
    }

    for (int point = 39; point < 75; point++) {
        indices.push_back(38); 
        indices.push_back(point); 
        indices.push_back(point + 1); 
    }

    for (int point = 1; point < 37; point++) {
        indices.push_back(point); 
        indices.push_back(point + 1); 
        indices.push_back(point + 37); 

        indices.push_back(point + 1); 
        indices.push_back(point + 37); 
        indices.push_back(point + 38); 
    }

    Mesh* cylinder = new Mesh("cylinder");

    cylinder->InitFromData(vertices, indices);
    return cylinder;
}

Mesh* object3D::createCone(glm::vec3 center, glm::vec3 color, float radius, float height) {
	std::vector<VertexFormat> vertices = {
		VertexFormat(center - glm::vec3(0, height / 2, 0), glm::vec3(0, 1, 0), color)
	};

    float angleUnit = glm::radians(360.0) / 36.0;
    for (int point = 0; point <= 36; point++) {
        vertices.push_back(
                VertexFormat(center + glm::vec3(radius * glm::cos(point * angleUnit), -height / 2, radius * glm::sin(point * angleUnit)), glm::vec3(0, 1, 0), color)
                );
    }
	
	vertices.push_back(VertexFormat(center + glm::vec3(0, height / 2, 0), glm::vec3(0, 1, 0), color));

    std::vector<unsigned int> indices;

    for (int point = 1; point < 37; point++) {
        indices.push_back(0); 
        indices.push_back(point); 
        indices.push_back(point + 1); 

        indices.push_back(0); 
        indices.push_back(point); 
        indices.push_back(38); 
    }

    Mesh* cylinder = new Mesh("cylinder");

    cylinder->InitFromData(vertices, indices);
    return cylinder;
}
