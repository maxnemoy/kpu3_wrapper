#ifndef _KPU_DATA_H
#define _KPU_DATA_H
// подключение необходимых заголовков
#include "rotary.h"
#include "button.h"
#include "motor.h"
#include "timer.h"
// подключение внешних зависимостистей
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
    Motor *motor;
    Timer *timer;
    Boozer *boozer;
    Adafruit_SSD1306 *display;
    std::vector<MenuItem *> items;
    bool isWork;
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