#ifndef _BOOZER_H
#define _BOOZER_H

#include <Tone32.h>

class Boozer {
    public:
        Boozer(int pin);
        void onMenuClick();
        void onMenuSelect();
        void onTimerEnd();
    private:
        int _pin;
        std::vector<int> _melody = std::vector<int>{NOTE_C4, NOTE_C5, NOTE_C6,};
};

#endif