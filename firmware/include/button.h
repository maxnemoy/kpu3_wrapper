#ifndef _BUTTON_H
#define _BUTTON_H

#include "menu.h"
#include "OneButton.h"

class Button{
    private:
        OneButton _button;
    public:
        Button(Menu *m);
        Menu *menu;
        void begin(int pin, bool mode);
        void tick();
};

#endif