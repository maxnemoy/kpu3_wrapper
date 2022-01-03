#include "menu_item.h"

BoolMenuItem::BoolMenuItem(String title, int id, bool defaultValue, bool isSelectable) : MenuItem(title, id, isSelectable){
    _defaultValue = defaultValue;
    _value = _defaultValue;
}

String BoolMenuItem::printValue(){
    return _value ? "On" : "Off";
}

bool BoolMenuItem::getValueBool(){
    return _value;
}

void BoolMenuItem::setValue(bool value){
    _value = value;
}

void BoolMenuItem::add(){
    if(_value) _value = false;
    else _value = true;
}

void BoolMenuItem::remove(){
    if(_value) _value = false;
    else _value = true;
}

void BoolMenuItem::reset(){
    _value = _defaultValue;
}