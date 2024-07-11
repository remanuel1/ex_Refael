#include "Cmd.h"
Cmd::Cmd(float init_time, int init_numUav, float init_destinationX, float init_destinationY)
{
	time = init_time;
	numUav = init_numUav;
	destinationX = init_destinationX;
	destinationY = init_destinationY;
}
float Cmd::getTime()
{
	return time;
}
int Cmd::getNumUav()
{
	return numUav;
}
float Cmd::getDesX()
{
	return destinationX;
}
float Cmd::getDesY()
{
	return destinationY;
}
