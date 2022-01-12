// подключение необходимых заголовочных файлов
#include "motor.h"
// Определение конструктора
Motor::Motor(int pin){
    _pin = pin;
    pinMode(_pin, OUTPUT);
    //инициализация разъема микроконтроллера 
    //для работы в режиме генерации ШИМ 
    ledcSetup(_pwmChannel, _freq, _resolution);
    ledcAttachPin(_pin, _pwmChannel);
    stop();
}
// определение функции включения двигателя
void Motor::start(int speed){
    ledcWrite(_pwmChannel, 0);
}
// определение функции отключения двигателя
void Motor::stop(){
    ledcWrite(_pwmChannel, 255);
}
