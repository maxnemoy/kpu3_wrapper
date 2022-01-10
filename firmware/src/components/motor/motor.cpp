#include "motor.h"

Motor::Motor(int pin){
    _pin = pin;
    pinMode(_pin, OUTPUT);
    ledcSetup(_pwmChannel, _freq, _resolution);
    ledcAttachPin(_pin, _pwmChannel);
    stop();
}

void Motor::start(int speed){
    ledcWrite(_pwmChannel, 0);
}

void Motor::stop(){
    ledcWrite(_pwmChannel, 255);
}
