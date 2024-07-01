#pragma once

#include "Solid.h"
#include <vector>

class Sphere : public Solid
{
public:

	Sphere() = default;

	Sphere(float radius, glm::vec3 center, unsigned int num_lat, unsigned int num_long) : Solid(center) {
		this->radius = radius;
		
		this->num_lat = num_lat;
		this->num_long = num_long;
		set_indices();
		set_vertices();
	}

private:
	float radius;
	unsigned int num_lat;
	unsigned int num_long;

	void set_indices();
	void set_vertices(); //normals and points
};

