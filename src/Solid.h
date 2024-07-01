#pragma once

#include <vector>
#include <glm/glm.hpp>

class Solid //all 3d object classes inherit this
{
public:

	Solid(glm::vec3 center) {
		this->center = center;
	}

	std::vector<glm::vec3> get_points() {
		return points;
	}
	std::vector<unsigned int> get_indices() {
		return indices;
	}
	std::vector<glm::vec3> get_normals() {
		return normals;
	}

	std::vector<float> get_vertices(bool use_normals) {
		
		std::vector<float> vertices;

			for (unsigned int i = 0; i < points.size(); i++) { 
				vertices.push_back(points[i].x);
				vertices.push_back(points[i].y);
				vertices.push_back(points[i].z);

				if (use_normals) {
					vertices.push_back(normals[i].x);
					vertices.push_back(normals[i].y);
					vertices.push_back(normals[i].z);
				}
				
			}
			
		return vertices;
	}

	void rotate_x(float angle);
	void rotate_y(float angle);
	void rotate_z(float angle);
	void scale(float size);
	void translate(glm::vec3 delta);

protected:
	std::vector<glm::vec3> points;
	std::vector<unsigned int> indices;
	std::vector<glm::vec3> normals;

	glm::vec3 center; //should be roughly center of mass, its the point that things rotate and scale based on
};

