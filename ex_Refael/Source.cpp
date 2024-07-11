#include "UAV.h"
#include "Cmd.h"
#include "System.h"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string> 
#include <corecrt_math_defines.h>
using namespace std;

int countLine(fstream &file)
{
    if (file.is_open()) {
        string line;
        int lineCount = 0;

        while (getline(file, line)) {
            lineCount++;
        }

        file.close();
        return lineCount;
    }
    else {
        cout << "Failed to open the file." << endl;
        return 0;
    }
}

bool compareCmdTime(Cmd* a, Cmd* b) {
    return a->getTime() < b->getTime();
}

float roundToTwoDecimals(float number) {
    return round(number * 100.0) / 100.0;
}

void updateLocation(float time, float speed ,UAV* uav, float radius)
{
    if (uav->getState() == State::MOVE)
    {
        float angle_radians = uav->getAzimuth() * M_PI / 180.0;
        float distance = speed * time;

        // Calculate new location
        float new_x = uav->getLocation().getX() + distance * cos(angle_radians);
        float new_y = uav->getLocation().getY() + distance * sin(angle_radians);

        uav->setLocation(new_x, new_y, uav->getLocation().getZ());
        if (abs(uav->getLocation() - uav->getDestination()) < distance)
        {
            uav->setState(State::RADIUS);
            uav->setLocation(uav->getDestination().getX(), uav->getDestination().getY(), uav->getLocation().getZ());
        }
    }
    else
    {
        //Advance the UAV to be in a circle around the destination
        if (uav->getState() == State::RADIUS)
        {
            float new_x, new_y;
            float angle_radians = uav->getAzimuth() * M_PI / 180.0;
            float distance = speed * time;
            new_x = uav->getLocation().getX() + distance * cos(angle_radians);
            new_y = uav->getLocation().getY() + distance * sin(angle_radians);

            float deltaX = new_x - uav->getDestination().getX();
            float deltaY = new_y - uav->getDestination().getY();
            distance = sqrt(deltaX * deltaX + deltaY * deltaY);
            if (distance >= radius)
            {
                uav->setState(State::REST);
                new_x = uav->getDestination().getX() + radius * cos(angle_radians);
                new_y = uav->getDestination().getY() + radius * sin(angle_radians);
            }
            
            uav->setLocation(new_x, new_y, uav->getLocation().getZ());

        }
        else
        {
            //REST STATE
            float currentAngle = atan2(uav->getLocation().getY() - uav->getDestination().getY(), uav->getLocation().getX() - uav->getDestination().getX());
            float angularDisplacement = (speed * time) / radius;
            float newAngle = currentAngle - angularDisplacement;

            float new_x = uav->getDestination().getX() + radius * cos(newAngle);
            float new_y = uav->getDestination().getY() + radius * sin(newAngle);
            float new_azimuth = atan2(new_y - uav->getLocation().getY(), new_x - uav->getLocation().getX());
            new_azimuth = new_azimuth * (180.0 / M_PI);
            if (new_azimuth < 0) {
                new_azimuth += 360.0;
            }

            uav->setLocation(new_x, new_y, uav->getLocation().getZ());
            uav->setAzimuth(new_azimuth);

        }
    }
}

void updateDestination(UAV* uav, float desX, float desY)
{
    float deltaX = desX - uav->getLocation().getX();
    float deltaY = desY - uav->getLocation().getY();

    float angleRadians = atan2(deltaY, deltaX);
    float angleDegrees = angleRadians * 180.0 / M_PI;

    if (angleDegrees < 0) {
        angleDegrees += 360.0;
    }
    uav->setAzimuth(angleDegrees);
    uav->setDestination(desX, desY, uav->getLocation().getZ());
    uav->setState(State::MOVE);
}

void deleteAll(UAV** uavs, int numUav, Cmd** cmds, int numCmd)
{
    for (int i = 0; i < numUav; ++i) {
        delete uavs[i];
    }
    for (int i = 0; i < numCmd; ++i) {
        delete cmds[i];
    }
}

int main()
{

    UAV** uavs;
    Cmd** cmds;
    System system("SimParams.ini");

    uavs = new UAV* [system.getNumUavs()];
    for (int i = 0; i < system.getNumUavs(); i++)
    {
        uavs[i] = new UAV(State::MOVE, system.getX0(), system.getY0(), system.getZ0(), system.getAzimuth());
    }

    fstream fileCmd("SimCmds.txt");
    if (!fileCmd.is_open()) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }
    int sumLine = countLine(fileCmd);
    fileCmd.open("SimCmds.txt");
    cmds = new Cmd*[sumLine];
    string line;
    for (int i = 0; i < sumLine; i++)
    {
        getline(fileCmd, line);
        try
        {
            istringstream iss(line);
            float time, destinationX, destinationY;
            int numUav;

            if (!(iss >> time >> numUav >> destinationX >> destinationY)) {
                throw ("Error parsing line");
            }
            else
            {
                cmds[i] = new Cmd(time, numUav, destinationX, destinationY);
            }
        }
        catch (const string e) {
            cout << "Error parsing line: " << line << endl;
        }
        
    }

    // sort cmds by time
    sort(cmds, cmds + sumLine, compareCmdTime);

    // open filws for each UAV
    ofstream** uavFiles = new ofstream * [system.getNumUavs()];
    for (int i = 0; i < system.getNumUavs(); i++) {
        string fileName = "UAV_" + to_string(i) + ".txt";
        uavFiles[i] = new ofstream(fileName);
        if (!(*uavFiles[i])) {
            cerr << "Failed to open file for UAV " << i << endl;
            return 1;
        }
    }

    int n_command = 0;
    for (int i = 0; i < system.getTimeLim() / system.getDt(); i++)
    {
        for (int j = 0; j < system.getNumUavs(); j++)
        {
            int command = cmds[n_command]->getTime() / (system.getDt());
            if (i == (cmds[n_command]->getTime()/(system.getDt())) && cmds[n_command]->getNumUav() == j)
            {
                updateDestination(uavs[j], cmds[n_command]->getDesX(), cmds[n_command]->getDesY());
                if (n_command < sumLine - 1)
                {
                    n_command++;
                }
            }
            updateLocation(system.getDt(), system.getSpeed(), uavs[j], system.getRadius());
            *uavFiles[j] << i << " " << roundToTwoDecimals(uavs[j]->getLocation().getX()) << " " << roundToTwoDecimals(uavs[j]->getLocation().getY()) << " " << roundToTwoDecimals(uavs[j]->getAzimuth()) << endl;
        }
    }
    
    for (int i = 0; i < system.getNumUavs(); i++)
    {
        uavFiles[i]->close();
    }

    deleteAll(uavs, system.getNumUavs(), cmds, sumLine);

}


