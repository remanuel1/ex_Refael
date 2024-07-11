#include "System.h"

System::System(string file)
{
	INIReader reader(file);
	if (reader.ParseError() != 0) {
		cout << "Can't load 'config.ini'\n";
		return;
	}
	dt = stof(reader.GetString("Parameters", "Dt", "0.001"));
	numUavs = stoi(reader.GetString("Parameters", "N_uav", "1"));
	radius = stof(reader.GetString("Parameters", "R", "1"));
	x0 = stof(reader.GetString("Parameters", "X0", "0"));
	y0 = stof(reader.GetString("Parameters", "Y0", "0"));
	z0 = stof(reader.GetString("Parameters", "Z0", "0"));
	speed = stof(reader.GetString("Parameters", "V0", "50"));
	azimuth = stof(reader.GetString("Parameters", "Az", "20"));
	timeLim = stof(reader.GetString("Parameters", "Time_Lim", "30"));
}

float System::getDt()
{
	return dt;
}
float System::getX0()
{
	return x0;
}
float System::getY0()
{
	return y0;
}
float System::getZ0()
{
	return z0;
}
int System::getNumUavs()
{
	return numUavs;
}
float System::getRadius()
{
	return radius;
}
float System::getSpeed()
{
	return speed;
}
float System::getAzimuth()
{
	return azimuth;
}
float System::getTimeLim()
{
	return timeLim;
}