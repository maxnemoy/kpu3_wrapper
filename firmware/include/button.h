#ifndef _BUTTON_H
#define _BUTTON_H
// подключение необходимых заголовков
#include "menu.h"
#include "motor.h"
// подключение внешней зависимости
#include "OneButton.h"
// объявление объекта
class Button{
    private:
        OneButton _button;
    public:
        Button(Menu *m, Motor *motor);
        Menu *menu;
        Motor *motor;
        void begin(int pin, bool mode);
        void tick();
};

#endif