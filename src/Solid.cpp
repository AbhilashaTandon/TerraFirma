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
	for (int i = 0; i < points.size()-2; i += 3) {
		points[i] = (points[i] - center_x) * size + center_x;
		points[i + 1] = (points[i + 1] - center_y) * size + center_y;
		points[i + 2] = (points[i + 2] - center_z) * size + center_z;
	}
}

void Solid::translate(float dx, float dy, float dz)
{
	for (int i = 0; i < points.size()-2; i+=3) {
		points[i] += dx;
		points[i + 1] += dy;
		points[i + 2] += dz;
	}
}
