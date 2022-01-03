#include "menu_item.h"

FloatMenuItem::FloatMenuItem(String title, int id, float defaultValue, float step, bool isSelectable) : MenuItem(title, id, isSelectable){
    _defaultValue = defaultValue;
    _value = _defaultValue;
    _step = step;
}

String FloatMenuItem::printValue(){
    return String(_value);
}

float FloatMenuItem::getValueFloat(){
    return _value;
}

void FloatMenuItem::setValue(float value){
    _value = value;
}

void FloatMenuItem::add(){
    _value += _step;
}

void FloatMenuItem::remove(){
    _value -= _step;
}

void FloatMenuItem::reset(){
    _value = _defaultValue;
}