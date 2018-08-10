#ifndef _CC_TIMER_H_
#define _CC_TIMER_H_

#include <SDL.h>
#include <iostream>
#include <inttypes.h>

namespace cc
{
class Timer
{
public:
    Timer();
    ~Timer();

public:
    void start();
    void stop();
    void pause();
    void resume();
    uint32_t getTicks();
    bool isStarted();
    bool isPaused();
    uint32_t getDeltaTime();

protected:
    uint32_t _startTicks;
    uint32_t _pausedTicks;
    bool _started;
    bool _paused;
    uint32_t _lastTicks;
};
};

#endif