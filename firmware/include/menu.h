#ifndef _MENU_H
#define _MENU_H

#include <Arduino.h>

class Menu{
    public:
        Menu(std::vector<MenuItem *> menuItems, Sensor *sensor);
        void next();
        void previous();
        void select();
        // void hold();
        // void release();
        void reset();
        std::vector<String> getMenu();
        int index();
        void setValue(int id, float value);
        void setValue(int id, bool value);
        float getFloatValue(int id);
        void updateData();
    private:
        int selectedItem = -1;
        int item = 0;
        std::vector<MenuItem *> items;
        Sensor* sensor;
};

Menu::Menu(std::vector<MenuItem *> menuItems, Sensor *sense){
    items = menuItems;
    sensor = sense;
}

std::vector<String> Menu::getMenu(){
    std::vector<String> menu = {};
    for(int i = 0; i < items.size(); i++){
        String leading = "  ";
        if(item == i) { leading = "> ";}
        if(selectedItem == i) { leading = ">>";}

        menu.insert(menu.end(), leading + items[i]->name + " " + items[i]->printValue());
    }
    return menu;
}

int Menu::index(){
    return item;
}

void Menu::next(){
    if(selectedItem == item){
        items[selectedItem]->add();
        return;
    }
    item++;
    if(item == items.size()) {item = 0;}
}

void Menu::previous(){
    if(selectedItem == item){
        items[selectedItem]->remove();
        return;
    }
    item--;
    if(item < 0) {item = items.size()-1;}
}

void Menu::select(){
    if(items[item]->isSelectable){
        if(selectedItem == item) {
            selectedItem = -1;
            return;
        }
        selectedItem = item;
    }
}

void Menu::reset(){
    if(selectedItem == item){
        items[selectedItem]->reset();
        return;
    }
    selectedItem = -1;
    item = 0;
}

void Menu::setValue(int id, float value){
    for(int i = 0; i < items.size(); i++){
        if(items[i]->id == id){
            items[i]->setValue(value);
        }
    }
}

void Menu::setValue(int id, bool value){
    for(int i = 0; i < items.size(); i++){
        if(items[i]->id == id){
            items[i]->setValue(value);
        }
    }
}

float Menu::getFloatValue(int id){
    for(int i = 0; i < items.size(); i++){
        if(items[i]->id == id){
            return items[i]->getValueFloat();
        }
    }
}

void Menu::updateData(){
    if(selectedItem == item && items[selectedItem]->id == SCALE_ITEM){
        sensor->setScaleFactor(items[selectedItem]->getValueFloat());
    }
}

#endif