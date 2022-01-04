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
};
#endif

