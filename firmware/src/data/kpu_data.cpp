#include "kpu_data.h"

KpuData::KpuData()
{
    encoder = new Rotary(encoderS2Pin, encoderS1Pin);
    display = new Adafruit_SSD1306(128, 64, &Wire);
    items = {
        new BoolMenuItem("run", IS_RUN_ITEM),
        new FloatMenuItem("cur. psi", PSI_VALUE_ITEM, 56.05, 0.05, false),
        new FloatMenuItem("cur. mm/m", MMoM_VALUE_ITEM, 56.05, 0.05, false),
        new FloatMenuItem("scale", SCALE_ITEM, 56.05, 0.05),
        new BoolMenuItem("is vacuum", IS_VACUUM_ITEM),
        new FloatMenuItem("comp. limit", C_LIMIT_ITEM, 730.0, 1.0),
        new FloatMenuItem("vac. limit", V_LIMIT_ITEM, 700.0, 1.0),
    };
    sensor = new Sensor(sensorDataPin, sensorSckPin);
    menu = new Menu(items, sensor);
    button = new Button(menu);
    motor = new Motor(motorPin);
}

void KpuData::begin(){
    encoder->begin(true, false);
    button->begin(encoderKeyPin, true);   
}