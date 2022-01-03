#ifndef _KPU_DATA_H
#define _KPU_DATA_H

#include "rotary.h"
#include "button.h"

#include "Wire.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

class KpuData
{
public:
    KpuData();
    Menu *menu;
    Sensor *sensor;
    Rotary *encoder;
    Button *button;
    Adafruit_SSD1306 *display;
    std::vector<MenuItem *> items;

    void begin();
private:
    int motorPin = 14;
    int encoderS1Pin = 27;
    int encoderS2Pin = 26;
    int encoderKeyPin = 25;
    int sensorDataPin = 4;
    int sensorSckPin = 2;
};

#endif