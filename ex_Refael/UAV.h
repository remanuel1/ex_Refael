#pragma once
#include "Point3d.h"
#include <iostream>
using namespace std;

enum class State {
	MOVE,
    RADIUS,
	REST
};

class UAV
{
private:
    Point3d location;
    Point3d destination;
	float azimuth;
	State state;

public:

    UAV(State initState, float initX, float initY, float initZ, float initAzimuth);

    // Getters
    State getState();
    Point3d getLocation();
    Point3d getDestination();
    float getAzimuth();

    // Setters
    void setState(State newState);
    void setLocation(float newX, float newY, float newZ);
    void setDestination(float newX, float newY, float newZ);
    void setAzimuth(float newAzimuth);

};

