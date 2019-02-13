#include <iostream>
#include "TimeManager.h"
using namespace std::chrono;

TimeManager TimeManager::instance;


TimeManager& TimeManager::getInstance()
{
	return instance;
}

void TimeManager::startup()
{
	startTime = high_resolution_clock::now();

	lastTime = 0;
	numberOfFrames = 0;
	currentNumberOfFrames = 0;
}



void TimeManager::shutdown()
{
	frameTime = 0;
	time = 0;
	lastTime = 0;
	numberOfFrames = 0;
}

const double& TimeManager::getTime() const
{
	return time;
}

const double& TimeManager::getFixedTimestep() const
{
	return fixedTimestep;
}

const double& TimeManager::getFrameTime() const
{
	return frameTime;
}

const int& TimeManager::getFps() const
{
	return fps;
}

void TimeManager::setFixedTimestep(const double& value)
{
	fixedTimestep = value;
}

void TimeManager::setFixedTimestep(const double&& value)
{
	fixedTimestep = value;
}

void TimeManager::updateTimeAndFrameTime() {
    // Retreive time
    passedTime = high_resolution_clock::now();
    time = duration_cast<duration<double>>(passedTime - startTime).count();
    //std::cout<< "time : "<< time << std::endl;
    // Frame time
    frameTime = time - previeousFrameTime;
    previeousFrameTime = time;
}

void TimeManager::updateFPS() {
    // Frames per seconds
    numberOfFrames++;
    if (time - lastTime >= 1.0)
    {
        fps = numberOfFrames;
        currentNumberOfFrames = numberOfFrames;
        numberOfFrames = 0;
        lastTime++;
    }

}
