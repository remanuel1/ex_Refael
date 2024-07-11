#include "Point3d.h"
#include <cmath>

Point3d::Point3d()
{
	x = 0;
	y = 0;
	z = 0;
}
Point3d::Point3d(float init_x, float init_y, float init_z)
{
	x = init_x;
	y = init_y;
	z = init_z;
}

float Point3d::getX()
{
	return x;
}
float Point3d::getY()
{
	return y;
}
float Point3d::getZ()
{
	return z;
}
void Point3d::setPoint(float s_x, float s_y, float s_z)
{
	x = s_x;
	y = s_y;
	z = s_z;
}

void Point3d::setX(float init_x)
{
	x = init_x;
}
void Point3d::setY(float init_y)
{
	y = init_y;
}
void Point3d::setZ(float init_z)
{
	z = init_z;
}

float operator-(const Point3d& point1, const Point3d& point2) {
	return point2.x - point1.x + point2.y - point1.y;
}



