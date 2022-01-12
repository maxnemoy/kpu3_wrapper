// подключение необходимых заголовочных файлов
#include "boozer.h"
// Определение конструктора
Boozer::Boozer(int pin, int channel){
    _pin = pin;
    _channel = channel;
    pinMode(_pin, OUTPUT);
    noTone(_pin, _channel);
}
// определение функции воспроизведения звука
// при переключении пунктов меню
void Boozer::onMenuClick(){
    tone(_pin, NOTE_F5, 50, _channel);
    noTone(_pin, _channel);
};
// определение функции воспроизведения звука
// при выборе пункта меню
void Boozer::onMenuSelect(){
    tone(_pin, NOTE_G5, 50, _channel);
    noTone(_pin, _channel);
};
// определение функции воспроизведения звука
// при завершении работы таймера
void Boozer::onTimerEnd(){
    for(int i = 0; i < 3; i++){
        for(int i = 0; i < _melody.size(); i++){
            tone(_pin, _melody[i], 500, _channel);
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    noTone(_pin, _channel);
};