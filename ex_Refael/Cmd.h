#pragma once
class Cmd
{
	float time;
	int numUav;
	float destinationX;
	float destinationY;

public:
	Cmd(float init_time, int init_numUav, float init_destinationX, float init_destinationY);
	float getTime();
	int getNumUav();
	float getDesX();
	float getDesY();
};

