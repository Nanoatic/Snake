#pragma once

#include <chrono>

class TimeManager {
public:
    static TimeManager &getInstance();

    void startup();


    void shutdown();

    // Getters
    const double &getTime() const;

    const double &getFixedTimestep() const;

    const double &getFrameTime() const;

    const int &getFps() const;

    // Setters
    void setFixedTimestep(const double &value);

    void setFixedTimestep(const double &&value);

    void updateFPS();
    void updateTimeAndFrameTime();

private:
    TimeManager() = default;

    std::chrono::high_resolution_clock::time_point startTime;
    std::chrono::high_resolution_clock::time_point passedTime;
    static TimeManager instance;
    double time = 0;
    double frameTime = 0;
    double fixedTimestep = 0.033; // 30 fps
    int fps = 0;

    double previeousFrameTime = 0;
    double lastTime = 0;
    int numberOfFrames = 0;
    int currentNumberOfFrames = 0;


};
