#include "menu.h"

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
    if(items[item]->id == IS_RUN_ITEM){
        setValue(CHANGES_ITEM, 0.001f);
    }

    if(items[item]->isSelectable){
        if(selectedItem == item) {
            selectedItem = -1;
            return;
        }
        selectedItem = item;
    }
}

void Menu::unSelect(){
    selectedItem = -1;
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

void Menu::updateData(){
    if(selectedItem == item && items[selectedItem]->id == SCALE_ITEM){
        sensor->setScaleFactor(items[selectedItem]->getValueFloat());
    }
}

bool Menu::getBoolValue(int id){
     for(int i = 0; i < items.size(); i++){
        if(items[i]->id == id){
            return items[i]->getValueBool();
        }
    }
    return false;
}

float Menu::getFloatValue(int id){
    for(int i = 0; i < items.size(); i++){
        if(items[i]->id == id){
            return items[i]->getValueFloat();
        }
    }
    return false;
}