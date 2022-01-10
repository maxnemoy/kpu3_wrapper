#include "boozer.h"

Boozer::Boozer(int pin, int channel){
    _pin = pin;
    _channel = channel;
    pinMode(_pin, OUTPUT);
    //noTone(_pin, _channel);
}

void Boozer::onMenuClick(){
    tone(_pin, NOTE_F5, 50, 1);
    noTone(_pin, _channel);
};

void Boozer::onMenuSelect(){
    tone(_pin, NOTE_G5, 50, 1);
    noTone(_pin, _channel);
};

void Boozer::onTimerEnd(){
    for(int i = 0; i < 3; i++){
        for(int i = 0; i < _melody.size(); i++){
            tone(_pin, _melody[i], 500, 1);
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    noTone(_pin, _channel);
};