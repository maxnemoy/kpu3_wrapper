#ifndef _MOTOR_H
#define _MOTOR_H
// подключение внешней зависимости
#include "Arduino.h"
// объявление объекта
class Motor{
    public:
        Motor(int pin);
        void start(int speed);
        void stop();
    private:
        int _pin;
        const int _freq = 30000;
        const int _pwmChannel = 0;
        const int _resolution = 8;
};
#endif

