#include "kpu_data.h"

KpuData::KpuData()
{
    isWork = true;
    encoder = new Rotary(encoderS2Pin, encoderS1Pin);
    display = new Adafruit_SSD1306(128, 64, &Wire);
    items = {
        new BoolMenuItem("run", IS_RUN_ITEM),
        new FloatMenuItem("cur. psi", PSI_VALUE_ITEM, 56.05, 0.05, false),
        new FloatMenuItem("cur. mm/m", MMoM_VALUE_ITEM, 56.05, 0.05, false),
        new FloatMenuItem("scale", SCALE_ITEM, 56.05, 0.05),
        new BoolMenuItem("is vacuum", IS_VACUUM_ITEM),
        new FloatMenuItem("comp. limit", C_LIMIT_ITEM, 800.0, 1.0),
        new FloatMenuItem("vac. limit", V_LIMIT_ITEM, 700.0, 1.0),
        new FloatMenuItem("difference", CHANGES_ITEM, 0.001, 1.0, false),
    };
    sensor = new Sensor(sensorDataPin, sensorSckPin);
    menu = new Menu(items, sensor);
    motor = new Motor(motorPin);
    button = new Button(menu, motor);

    onTick* tick = [](int t) { 
            Serial.println("tick"); 
            Serial.println(t);
        };

    onTimerEnd* end = [](Menu *menu) {
            Serial.println("end");
            if(menu->getBoolValue(IS_VACUUM_ITEM)){
                menu->setValue(CHANGES_ITEM, menu->getFloatValue(V_LIMIT_ITEM) - menu->getFloatValue(MMoM_VALUE_ITEM));
            } else {
                menu->setValue(CHANGES_ITEM, menu->getFloatValue(C_LIMIT_ITEM) - menu->getFloatValue(MMoM_VALUE_ITEM));
            }
        };
    timer = new Timer(10, menu, tick, end);
}

void KpuData::begin(){
    encoder->begin(true, false);
    button->begin(encoderKeyPin, true);   
}