#include "object2D.h"

#include <iostream>
#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateCeva(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, -length, 0), color),
        VertexFormat(corner + glm::vec3(0, -length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateTankFirstBase(const std::string &name, glm::vec3 center, glm::vec3 color, float length) {
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center + glm::vec3(-4.5 * length, 0, 0), color),
        VertexFormat(center + glm::vec3(-5 * length, length, 0), color),
        VertexFormat(center + glm::vec3(5 * length, length, 0), color),
        VertexFormat(center + glm::vec3(4.5 * length, 0, 0), color)
    };

    Mesh* base = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3, 0, 2 };

    base->InitFromData(vertices, indices);
    return base;
}

Mesh* object2D::CreateTankSecondBase(const std::string &name, glm::vec3 center, glm::vec3 color, float length) {
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center + glm::vec3(-6.5 * length, 0, 0), color),
        VertexFormat(center + glm::vec3(-5.5 * length, 2 * length, 0), color),
        VertexFormat(center + glm::vec3(5.5 * length, 2 * length, 0), color),
        VertexFormat(center + glm::vec3(6.5 * length, 0, 0), color)
    };

    Mesh* base = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3, 0, 2 };

    base->InitFromData(vertices, indices);
    return base;
}

Mesh* object2D::CreateTankTop(const std::string &name, glm::vec3 center, glm::vec3 color, float radius) {
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center, color)
    };

    float angleUnit = glm::radians(180.0) / 20.0;
    for (int point = 0; point <= 20; point++) {
        vertices.push_back(
                VertexFormat(center + glm::vec3(radius * glm::cos(point * angleUnit), radius * glm::sin(point * angleUnit), 0), color)
                );
    }

    std::vector<unsigned int> indices;

    for (int point = 1; point < 21; point++) {
        indices.push_back(0); 
        indices.push_back(point); 
        indices.push_back(point + 1); 
    }

    Mesh* top = new Mesh(name);

    top->InitFromData(vertices, indices);
    return top;
}
