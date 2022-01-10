#include "button.h"

Button::Button(Menu *m,  Motor *mt){
    menu = m;
    motor = mt;
}

void Button::tick(){
    _button.tick();
}

void onClick(void* btm){
    ((Button*)btm)->menu->select();
}
void onDoubleClick(void* btm){
    Button button = (*(Button*)btm);
    if(button.menu->getBoolValue(IS_RUN_ITEM)){
        button.menu->setValue(IS_RUN_ITEM, false);
        button.motor->stop();
        button.menu->unSelect();
    } else { 
        ((Button*)btm)->menu->reset();
    }
}
void onHold(){
    Serial.println("hold");
}
void onRelease(){
    Serial.println("release");
}

void Button::begin(int pin, bool mode = true){
    _button = OneButton(pin, mode);
    _button.attachClick(onClick, &_button);
    _button.attachDoubleClick(onDoubleClick, &_button);
}
