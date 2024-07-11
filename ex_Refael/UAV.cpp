#include "UAV.h"

UAV::UAV(State initState, float initX, float initY, float initZ, float initAzimuth)
{
	state = initState;
	location = Point3d(initX, initY, initZ);
	destination = Point3d();
	azimuth = initAzimuth;
}

// Getters
State UAV::getState()
{
	return state;
}

Point3d UAV::getLocation()
{
	return location;
}
Point3d UAV::getDestination()
{
	return destination;
}

float UAV::getAzimuth()
{
	return azimuth;
}

// Setters
void UAV::setState(State newState)
{
	state = newState;
}
void UAV::setLocation(float newX, float newY, float newZ)
{
	location = Point3d(newX, newY, newZ);
}
void UAV::setDestination(float newX, float newY, float newZ)
{
	destination = Point3d(newX, newY, newZ);
}
void UAV::setAzimuth(float newAzimuth)
{
	azimuth = newAzimuth;
}
