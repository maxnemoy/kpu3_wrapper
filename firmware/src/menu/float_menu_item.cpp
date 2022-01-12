// подключение необходимых заголовочных файлов
#include "menu_item.h"

// определение конструктора числового меню, 
// который является наследником абстрактного класса MenuItem
FloatMenuItem::FloatMenuItem(String title, int id, float defaultValue, float step, bool isSelectable) : MenuItem(title, id, isSelectable){
    _defaultValue = defaultValue;
    _value = _defaultValue;
    _step = step;
}

// пределение функции возврата значения
// с приведение его типа к строке
String FloatMenuItem::printValue(){
    return String(_value);
}

// определение функции возврата значения
float FloatMenuItem::getValueFloat(){
    return _value;
}

// определение функции установки значения
void FloatMenuItem::setValue(float value){
    _value = value;
}

// определение фукции увелечения 
// значения на шаг
void FloatMenuItem::add(){
    _value += _step;
}

// определение функции уменьшения
// значения на шаг
void FloatMenuItem::remove(){
    _value -= _step;
}

// определение функции сброса
// значения на значение по умолчанию
void FloatMenuItem::reset(){
    _value = _defaultValue;
}