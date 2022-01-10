#include "boozer.h"

Boozer::Boozer(int pin){
    _pin = pin;
    pinMode(_pin, OUTPUT);
}

void Boozer::onMenuClick(){
    tone(_pin, NOTE_F5, 50, 1);
};

void Boozer::onMenuSelect(){
    tone(_pin, NOTE_G5, 50, 1);
};

void Boozer::onTimerEnd(){
    for(int i = 0; i < 3; i++){
        for(int i = 0; i < _melody.size(); i++){
            tone(_pin, _melody[i], 500, 1);
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
};