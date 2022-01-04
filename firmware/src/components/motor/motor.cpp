#include "motor.h"

Motor::Motor(int pin){
    _pin = pin;
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
}

void Motor::start(int _){
    digitalWrite(_pin, HIGH);
}

void Motor::stop(){
    digitalWrite(_pin, LOW);
}
