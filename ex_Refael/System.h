#pragma once
#include <string>
#include "inih-master/ini.h"
#include "inih-master/cpp/INIReader.h"
#include <iostream>
using namespace std;

class System
{
private:
	float dt;
	float x0;
	float y0;
	float z0;
	int numUavs;
	float radius;
	float speed;
	float azimuth;
	float timeLim;

public:
	System(string file);
	float getDt();
	float getX0();
	float getY0();
	float getZ0();
	int getNumUavs();
	float getRadius();
	float getSpeed();
	float getAzimuth();
	float getTimeLim();
};

