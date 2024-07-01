#include "Sphere.h"
#include <cmath>
#include <iostream>

static const float tau = 6.283185307;

void Sphere::set_vertices()
{

	float x_coord, y_coord, z_coord;


	//north pole
	x_coord = 0;
	y_coord = 0;
	z_coord = radius;
	//vector norm

	points.push_back(center_x - x_coord);
	points.push_back(center_y - y_coord);
	points.push_back(center_z - z_coord);

	normals.push_back(x_coord / radius);
	normals.push_back(y_coord / radius);
	normals.push_back(z_coord / radius);

	for (float j = 1; j < num_lat; j += 1) { //excludes north and south poles
		for (float i = 0; i < num_long; i += 1) {

			//does rings at each latitude line down the sphere

			//math convention for spherical coordinates
			float phi = i * tau / (num_long);
			float theta = j * tau / (2 * num_lat);

			x_coord = radius * std::sin(theta) * std::cos(phi);
			y_coord = radius * std::sin(theta) * std::sin(phi); //y coord
			z_coord = radius * std::cos(theta); //z coord


			points.push_back(center_x - x_coord);
			points.push_back(center_y - y_coord);
			points.push_back(center_z - z_coord);

			normals.push_back(x_coord / radius);
			normals.push_back(y_coord / radius);
			normals.push_back(z_coord / radius);

			
		}
	}

	//south pole

	x_coord = 0;
	y_coord = 0;
	z_coord = -radius;


	points.push_back(center_x - x_coord);
	points.push_back(center_y - y_coord);
	points.push_back(center_z - z_coord);

	normals.push_back(x_coord / radius);
	normals.push_back(y_coord / radius);
	normals.push_back(z_coord / radius);

	
}

void Sphere::set_indices()
{
	for (int i = 0; i < num_long; i++) {

		indices.push_back(1 + i);
		indices.push_back(0); //north pole
		indices.push_back(1 + ((i + 1) % num_long));
		//adds triangle from north pole to first set of points
	}

	for (int j = 0; j < num_lat - 2; j++) {
		//add 2 triangles for each tile
		for (int i = 0; i < num_long; i += 1) {

			//next point on latitude circle

			unsigned int next_point = (i + 1) % num_long; //use modulus to wraparound

			indices.push_back(1 + j * num_long + i);
			indices.push_back(1 + (j + 1) * num_long + i); //down 1
			indices.push_back(1 + j * num_long + next_point); //right 1

			indices.push_back(1 + (j + 1) * num_long + next_point);
			indices.push_back(1 + (j + 1) * num_long + i); //down 1
			indices.push_back(1 + j * num_long + next_point); //right 1
		}
	}

	for (int i = 0; i < num_long; i++) {
		indices.push_back(1 + (num_lat - 2) * num_long + i); //last circle
		indices.push_back(1 + (num_lat - 2) * num_long + (i + 1) % num_long); //last circle next point
		indices.push_back((num_lat - 1) * (num_long)+1);
		//adds triangle from north pole to first set of points
	}
}

