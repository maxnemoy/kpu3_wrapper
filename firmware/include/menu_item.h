#pragma once

#include "Arduino.h"

class MenuItem{
    public:
        MenuItem(String title);
        String name;
        virtual String printValue() = 0;
        virtual void add() = 0;
        virtual void remove() = 0;
        virtual void reset() = 0;
};

MenuItem::MenuItem(String title){
    name = title;
}


class BoolMenuItem : public MenuItem{
    public:
        BoolMenuItem(String title, bool defaultValue = false);
        String printValue();
        void add();
        void remove();
        void reset();
    private: 
        bool _value;
        bool _defaultValue;
};

BoolMenuItem::BoolMenuItem(String title, bool defaultValue) : MenuItem(title){
    _defaultValue = defaultValue;
    _value = _defaultValue;
}

String BoolMenuItem::printValue(){
    return _value ? "On" : "Off";
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

class FloatMenuItem : public MenuItem{
    public:
        FloatMenuItem(String title, float defaultValue = 1.0, float step = 0.5);
        String printValue();
        void add();
        void remove();
        void reset();
    private: 
        float _value;
        float _defaultValue;
        float _step;
};

FloatMenuItem::FloatMenuItem(String title, float defaultValue, float step) : MenuItem(title){
    _defaultValue = defaultValue;
    _value = _defaultValue;
    _step = step;
}

String FloatMenuItem::printValue(){
    return String(_value) ;
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