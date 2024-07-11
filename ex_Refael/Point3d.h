#pragma once
class Point3d
{
	float x;
	float y;
	float z;

public:
	Point3d();
	Point3d(float init_x, float init_y, float init_z);
	float getX();
	float getY();
	float getZ();
	void setPoint(float s_x, float s_y, float s_z);
	void setX(float init_x);
	void setY(float init_y);
	void setZ(float init_z);
	friend float operator-(const Point3d& point1, const Point3d& point2);

};

