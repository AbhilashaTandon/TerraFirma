#include "Sphere.h"
#include <cmath>
#include <iostream>

static const float tau = 6.283185307f;

void Sphere::set_vertices()
{
	//north pole
	glm::vec3 current_vec = glm::vec3(0, 0, radius);

	points.push_back(center - current_vec);
	normals.push_back(current_vec / radius);
	//current vec is distance to center, we normalize it to get normal vector

	for (float j = 1; j < num_lat; j += 1) { //excludes north and south poles
		for (float i = 0; i < num_long; i += 1) {

			//does rings at each latitude line down the sphere

			//math convention for spherical coordinates
			float phi = i * tau / (num_long);
			float theta = j * tau / (2 * num_lat);

			//temp variables to add to vec3
			float x_coord = radius * std::sin(theta) * std::cos(phi);
			float y_coord = radius * std::sin(theta) * std::sin(phi);
			float z_coord = radius * std::cos(theta); 

			current_vec = glm::vec3(x_coord, y_coord, z_coord);

			points.push_back(center - current_vec);

			normals.push_back(current_vec / radius); //current vec is distance to center, we normalize it to get normal vector

			
		}
	}


	//south pole
	current_vec = glm::vec3(0, 0, -radius);

	points.push_back(center - current_vec);
	normals.push_back(current_vec / radius);

	
}

void Sphere::set_indices()
{
	for (unsigned int i = 0; i < num_long; i++) {

		indices.push_back(1 + i);
		indices.push_back(0); //north pole
		indices.push_back(1 + ((i + 1) % num_long));
		//adds triangle from north pole to first set of points
	}

	for (unsigned int j = 0; j < num_lat - 2; j++) {
		//add 2 triangles for each tile
		for (unsigned int i = 0; i < num_long; i += 1) {

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

	for (unsigned int i = 0; i < num_long; i++) {
		indices.push_back(1 + (num_lat - 2) * num_long + i); //last circle
		indices.push_back(1 + (num_lat - 2) * num_long + (i + 1) % num_long); //last circle next point
		indices.push_back((num_lat - 1) * (num_long)+1);
		//adds triangle from north pole to first set of points
	}
}

