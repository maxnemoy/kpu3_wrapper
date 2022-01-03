#include "sensor.h"

Sensor::Sensor(int data_pin, int sck_pin){
    _sensor.begin(data_pin, sck_pin, 64u);
    _sensor.set_scale(_scaleFactor);
}

float Sensor::getPsi(){
    return _sensor.get_units(_step);
}

float Sensor::getMillimetersOfMercury(){
    return (_sensor.get_units(20) / PSI_IN_MOM);
}

void Sensor::setStepSize(int step){
    _step = step;
};

void Sensor::setScaleFactor(float scale){
    _scaleFactor = scale;
    _sensor.set_scale(_scaleFactor);
};