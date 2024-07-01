#pragma once

#include "Solid.h"
#include <vector>

class Sphere : public Solid
{
public:

	Sphere() = default;

	Sphere(float radius, float center_x, float center_y, float center_z, unsigned int num_lat, unsigned int num_long) : Solid(center_x, center_y, center_z) {
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

