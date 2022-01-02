#ifndef _SENSOR_H
#define _SENSOR_H

#include "HX711.h"

class Sensor{  
    public:
        Sensor(int data_pin, int sck_pin);

        float getPsi();
        float getMillimetersOfMercury();
        
        void setStepSize(int step);
        void setScaleFactor(float scale);
    
    private:
        HX711 _sensor;
        float _scaleFactor = 56.05f;
        const float PSI_IN_MOM = 133.3224;
        int _step = 5;
};



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

Sensor::Sensor(int data_pin, int sck_pin){
    _sensor.begin(data_pin, sck_pin, 64u);
    _sensor.set_scale(_scaleFactor);
}

#endif