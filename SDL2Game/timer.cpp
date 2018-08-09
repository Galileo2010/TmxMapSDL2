#include "timer.h"

cc::Timer::Timer()
    : _startTicks(0)
    , _pausedTicks(0)
    , _started(false)
    , _paused(false)
    , _lastTicks(0)
{
}

cc::Timer::~Timer()
{
}

void cc::Timer::start()
{
    _started = true;
    _paused = false;
    _startTicks = SDL_GetTicks();
    _pausedTicks = 0;
}

void cc::Timer::stop()
{
    _started = false;
    _paused = false;
    _startTicks = 0;
    _pausedTicks = 0;
}

void cc::Timer::pause()
{
    if(_started && !_paused) {
        _paused = true;
        _pausedTicks = SDL_GetTicks() - _startTicks;
        _startTicks = 0;
    }
}

void cc::Timer::resume()
{
    if(_started && _paused) {
        _paused = false;
        _startTicks = SDL_GetTicks() - _pausedTicks;
        _pausedTicks = 0;
    }
}

uint32_t cc::Timer::getTicks()
{    
    if(!_started)
        return 0;
    if(_paused)
        return _pausedTicks;
    return SDL_GetTicks() - _startTicks;
}

bool cc::Timer::isStarted()
{
    return _started;
}

bool cc::Timer::isPaused()
{
    return _paused;
}
uint32_t cc::Timer::getDeltaTime()
{
    uint32_t delta = 0;
    delta = SDL_GetTicks() - _lastTicks;
    _lastTicks = SDL_GetTicks();
    return delta;
}
