#include "button.h"

Button::Button(Menu *m){
    menu = m;
}

void Button::tick(){
    _button.tick();
}

void onClick(void* btm){
    ((Button*)btm)->menu->select();
}
void onDoubleClick(void* btm){
    ((Button*)btm)->menu->reset();
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
