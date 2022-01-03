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

#endif