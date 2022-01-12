#ifndef _TIMER_H
#define _TIMER_H
// подключение необходимых заголовков
#include "menu.h"
// переопределение типа для функции вызываемой при шаге таймера
typedef void onTick(int t);
// переопределение типа для функции вызываемой при завершении таймера
typedef void onTimerEnd(Menu *menu);
// объявление объекта
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