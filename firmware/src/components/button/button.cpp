// подключение необходимых заголовочных файлов
#include "button.h"
// Определение конструктора
Button::Button(Menu *m,  Motor *mt){
    menu = m;
    motor = mt;
}
// определение функции обновления состояния кнопки
void Button::tick(){
    _button.tick();
}
// определение функции при однократном нажатии кнопки
void onClick(void* btm){
    //выбор текущего пункта меню
    ((Button*)btm)->menu->select();
}
// определение функции при двойном нажатии кнопки
void onDoubleClick(void* btm){
    Button button = (*(Button*)btm);
    //если находимя в рабочем режиме
    if(button.menu->getBoolValue(IS_RUN_ITEM)){
        //переходим в главное меню
        button.menu->setValue(IS_RUN_ITEM, false);
        //останавливаем работу мотора
        button.motor->stop();
        //снимаем выделение пункта run
        button.menu->unSelect();
    } else { //иначе
        // сбрасываем меню на значения по умолчанию
        ((Button*)btm)->menu->reset();
    }
}

// определение функции инициализации кнопки
void Button::begin(int pin, bool mode = true){
    _button = OneButton(pin, mode);
    _button.attachClick(onClick, &_button);
    _button.attachDoubleClick(onDoubleClick, &_button);
}
