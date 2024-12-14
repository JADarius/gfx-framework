#include <vector>

#include "Field.h"
#include <iostream>

using namespace std;


Field::Field(int n, int m) {
	vector<VertexFormat> vertices;

	for (int x = 0; x < n; x++) {
		for (int z = 0; z < m; z++) {
			vertices.push_back(VertexFormat(glm::vec3(x, 0, z)));
		}
	}

	vector<unsigned int> indices;

	for (int x = 0; x < n - 1; x++) {
		for (int z = 0; z < m - 1; z++) {
			// First triangle
			indices.push_back(x * m + z);
			indices.push_back((x + 1) * m + z);
			indices.push_back(x * m + z + 1);

			// Second triangle
			indices.push_back(x * m + z + 1);
			indices.push_back((x + 1) * m + z + 1);
			indices.push_back((x + 1) * m + z);
		}
	}

	body = new Mesh("field");
	body->InitFromData(vertices, indices);
}

Field::~Field() {
    //delete body;
}

Mesh* Field::getBody() {
	return body;
}
