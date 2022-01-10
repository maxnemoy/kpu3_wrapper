#ifndef _BUTTON_H
#define _BUTTON_H

#include "menu.h"
#include "motor.h"
#include "OneButton.h"


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