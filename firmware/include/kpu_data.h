#ifndef _KPU_DATA_H
#define _KPU_DATA_H

#include "sensor.h"
#include "menu_item.h"
#include "menu.h"
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

private:
    int motorPin = 14;
    int encoderS1Pin = 27;
    int encoderS2Pin = 26;
    int encoderKeyPin = 25;
    int sensorDataPin = 4;
    int sensorSckPin = 2;
};

KpuData::KpuData()
{
    encoder = new Rotary(encoderS2Pin, encoderS1Pin);
    display = new Adafruit_SSD1306(128, 64, &Wire);
    items = {
        new BoolMenuItem("run", IS_RUN_ITEM),
        new FloatMenuItem("cur. psi", PSI_VALUE_ITEM, 56.05, 0.05, false),
        new FloatMenuItem("cur. mm/m", MMoM_VALUE_ITEM, 56.05, 0.05, false),
        new BoolMenuItem("is vacuum", IS_VACUUM_ITEM),
        new FloatMenuItem("comp. limit", C_LIMIT_ITEM, 730.0, 1.0),
        new FloatMenuItem("vac. limit", V_LIMIT_ITEM, 700.0, 1.0),
        new FloatMenuItem("scale", SCALE_ITEM, 56.05, 0.05),
    };
    sensor = new Sensor(sensorDataPin, sensorSckPin);
    menu = new Menu(items, sensor);
    button = new Button(menu);
}

#endif