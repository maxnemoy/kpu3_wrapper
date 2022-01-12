// подключение необходимых заголовочных файлов
#include "timer.h"
// Определение конструктора
Timer::Timer(int seconds, Menu *menu, onTick tick, onTimerEnd end){
    _seconds = seconds;
    _currentSeconds = _seconds;
    _tick = tick;
    _end = end;
    _menu = menu;
    isRun = false;
}
// определение функции шага таймера
void Timer::tick(){
    // если текущее значение больше 0 
    // и таймер запущен
    if(_currentSeconds > 0 && isRun){
        //уменьшаем на единицу
        _currentSeconds -= 1;
        //вызываем замыкание шага
        (*_tick)(_currentSeconds);
        //если досчитали до 0
        if(_currentSeconds==0){
            // останавливаем таймер
            stop();
            // вызываем замыкание остановки таймера
            (*_end)(_menu);
        }
    }
}
// определение функции запроса
// текущего значения таймера
int Timer::getCurrent(){
    return _currentSeconds;
}
// определение функции начала
// работы таймера
void Timer::start(){
    _currentSeconds = _seconds;
    isRun = true;
}
//определение функции остановки таймера
void Timer::stop(){
    isRun = false;
}