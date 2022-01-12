#ifndef _BOOZER_H
#define _BOOZER_H
// подключение внешней зависимости
#include <Tone32.h>
// объявление объекта
class Boozer {
    public:
        Boozer(int pin, int channel = 1);
        void onMenuClick();
        void onMenuSelect();
        void onTimerEnd();
    private:
        int _pin;
        int _channel;
        std::vector<int> _melody = std::vector<int>{NOTE_C4, NOTE_C5, NOTE_C6,};
};

#endif