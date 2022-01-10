#include "timer.h"

Timer::Timer(int seconds, Menu *menu, onTick tick, onTimerEnd end){
    _seconds = seconds;
    _currentSeconds = _seconds;
    _tick = tick;
    _end = end;
    _menu = menu;
    isRun = false;
}

void Timer::tick(){
    if(_currentSeconds > 0){
        _currentSeconds -= 1;
        (*_tick)(_currentSeconds);
        if(_currentSeconds==0){
            stop();
            (*_end)(_menu);
        }
    }
}

int Timer::getCurrent(){
    return _currentSeconds;
}

void Timer::start(){
    _currentSeconds = _seconds;
    isRun = true;
}

void Timer::stop(){
    isRun = false;
}