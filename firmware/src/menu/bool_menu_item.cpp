// подключение необходимых заголовочных файлов
#include "menu_item.h"

// определение конструктора логического меню, 
// который является наследником абстрактного класса MenuItem
BoolMenuItem::BoolMenuItem(String title, int id, bool defaultValue, bool isSelectable) : MenuItem(title, id, isSelectable){
    _defaultValue = defaultValue;
    _value = _defaultValue;
}

// пределение функции возврата значения
// с приведение его типа к строке
String BoolMenuItem::printValue(){
    return _value ? "On" : "Off";
}

// определение функции возврата значения
bool BoolMenuItem::getValueBool(){
    return _value;
}

// определение функции установки значения
void BoolMenuItem::setValue(bool value){
    _value = value;
}

// определение фукции инверсии значения
void BoolMenuItem::add(){
    _value = !_value;
}

// определение фукции инверсии значения
void BoolMenuItem::remove(){
    _value = !_value;
}

// определение функции сброса
// значения на значение по умолчанию
void BoolMenuItem::reset(){
    _value = _defaultValue;
}