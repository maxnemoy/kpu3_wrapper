// подключение необходимых заголовочных файлов
#include "menu.h"

// определение конструктора
Menu::Menu(std::vector<MenuItem *> menuItems, Sensor *sense, Boozer *booz){
    items = menuItems;
    sensor = sense;
    boozer = booz;
}

// определение функции запроса текстового меню
std::vector<String> Menu::getMenu(){
    std::vector<String> menu = {};
    //перебор элементов меню
    for(int i = 0; i < items.size(); i++){ 
        String leading = "  ";
        //добавления символа текущего/выбранного элемента меню
        if(item == i) { leading = "> ";}
        if(selectedItem == i) { leading = ">>";}
        // добавления строки в массив элементов
        menu.insert(menu.end(), leading + items[i]->name + " " + items[i]->printValue());
    }
    return menu;
}

// определение функции возврата
// текущего элемента
int Menu::index(){
    return item;
}

// определение функции перехода к
// следующему пункту меню / управление
// выбранным пунктом
void Menu::next(){
    // воспроизведение звука
    boozer->onMenuClick();
    //если элемент выбран
    if(selectedItem == item){
        // увеличиваем его значение
        items[selectedItem]->add();
        return;
    }
    // переходим к следующему пункту меню
    item++;
    // если получившийся индекс пункта развен длине
    // массива всех пуктов, переходим к 1 элементу
    if(item == items.size()) {item = 0;}
}

// определение функции перехода к
// предыдущему пункту меню / управление
// выбранным пунктом
void Menu::previous(){
    // воспроизведение звука
    boozer->onMenuClick();
    //если элемент выбран
    if(selectedItem == item){
        // уменьшаем его значение
        items[selectedItem]->remove();
        return;
    }
    item--;
    // если получившийся индекс пункта меньше 0,
    // переходим к последнему элементу массива всех пуктов
    if(item < 0) {item = items.size()-1;}
}

// определение функции выбора меню
void Menu::select(){
    // если выделяемый пункт является запуском рабочего режима 
    if(items[item]->id == IS_RUN_ITEM){
        // обнуляем значение разницы показаний 
        setValue(CHANGES_ITEM, 0.001f);
    }
    // если элемент меню управляемый
    if(items[item]->isSelectable){
        // воспроизводим звук
        boozer->onMenuSelect();
        //если пункт выбран, снимаем выделение
        if(selectedItem == item) {
            selectedItem = -1;
            return;
        }
        // выделяем пункт
        selectedItem = item;
    }
}

//определение функции снятия выбора меню
void Menu::unSelect(){
    selectedItem = -1;
}

// определения функции 
// сброса состояния выбора/выделения меню
void Menu::reset(){
    if(selectedItem == item){
        items[selectedItem]->reset();
        return;
    }
    selectedItem = -1;
    item = 0;
}

// определение функции установки значений
// в числовой пункт меню 
void Menu::setValue(int id, float value){
    //перебор пунктов меню
    for(int i = 0; i < items.size(); i++){
        // если id пункта соответствует заданнаму
        if(items[i]->id == id){
            //устанавливаем ему новое значение
            items[i]->setValue(value);
        }
    }
}

// определение функции установки значений
// в логический пункт меню 
void Menu::setValue(int id, bool value){
    //перебор пунктов меню
    for(int i = 0; i < items.size(); i++){
        // если id пункта соответствует заданнаму
        if(items[i]->id == id){
            //устанавливаем ему новое значение
            items[i]->setValue(value);
        }
    }
}

// определение функции обновления
// обновления делителся (scale)
// после обновления его в пункте меню
void Menu::updateData(){
    // если обновленный пункт меню SCALE_ITEM
    if(selectedItem == item && items[selectedItem]->id == SCALE_ITEM){
        // устанавливаем новое значение для пересчета
        // показаний датчика давления в мм/рс
        sensor->setScaleFactor(items[selectedItem]->getValueFloat());
    }
}

// Запрос значения логического пункта меню 
bool Menu::getBoolValue(int id){
    //перебор пунктов меню
     for(int i = 0; i < items.size(); i++){
         // если id пункта соответствует заданнаму
        if(items[i]->id == id){
            // возвращаем его значение
            return items[i]->getValueBool();
        }
    }
    return false;
}

// Запрос значения числового меню 
float Menu::getFloatValue(int id){
    //перебор пунктов меню
    for(int i = 0; i < items.size(); i++){
        // если id пункта соответствует заданнаму
        if(items[i]->id == id){
            // возвращаем его значение
            return items[i]->getValueFloat();
        }
    }
    return false;
}