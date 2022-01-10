#ifndef _TIMER_H
#define _TIMER_H

#include "menu.h"

typedef void onTick(int t);
typedef void onTimerEnd(Menu *menu);

class Timer{
    public:
        Timer(int seconds, Menu *menu, onTick *tick, onTimerEnd *end);
        void start();
        void tick();
        void stop();
        int getCurrent();
        bool isRun;
    private:
        int _seconds;
        int _currentSeconds;
        onTick *_tick;
        onTimerEnd *_end;
        Menu *_menu;
};

#endif