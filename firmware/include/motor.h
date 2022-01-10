#ifndef _MOTOR_H
#define _MOTOR_H

#include "Arduino.h"

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

