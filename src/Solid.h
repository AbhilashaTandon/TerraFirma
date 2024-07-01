#pragma once

#include <vector>

class Solid
{
public:

	Solid(float center_x, float center_y, float center_z) {
		this->center_x = center_x;
		this->center_y = center_y;
		this->center_z = center_z;
	}

	std::vector<float> get_points() {
		return points;
	}
	std::vector<unsigned int> get_indices() {
		return indices;
	}
	std::vector<float> get_normals() {
		return normals;
	}

	std::vector<float> get_vertices(bool use_normals) {
		
		if (use_normals) {
			std::vector<float> vertices;

			for (unsigned int i = 0; i < points.size()-2; i+=3) { //3 dimensional
				vertices.push_back(points[i]);
				vertices.push_back(points[i + 1]);
				vertices.push_back(points[i + 2]);

				vertices.push_back(normals[i]);
				vertices.push_back(normals[i + 1]);
				vertices.push_back(normals[i + 2]);
				
			}
			return vertices;
		}
		else {
			return points;
		}
	}

	void rotate_x(float angle);
	void rotate_y(float angle);
	void rotate_z(float angle);
	void scale(float size);
	void translate(float dx, float dy, float dz);

protected:
	std::vector<float> points;
	std::vector<unsigned int> indices;
	std::vector<float> normals;

	float center_x;
	float center_y;
	float center_z;
};

