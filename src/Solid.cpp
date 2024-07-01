#include "Solid.h"

void Solid::rotate_x(float angle)
{
}

void Solid::rotate_y(float angle)
{
}

void Solid::rotate_z(float angle)
{
}

void Solid::scale(float size)
{
	for (int i = 0; i < points.size(); i ++) {
		points[i] = (points[i] - center) * size + center;
	}
}

void Solid::translate(glm::vec3 delta)
{
	for (int i = 0; i < points.size(); i++) {
		points[i] += delta;
	}
	center += delta;
}
