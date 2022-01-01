#pragma once

#include <Arduino.h>
#include <menu_item.h>

class Menu{
    public:
        void next();
        void previous();
        void select();
        // void hold();
        // void release();
        void reset();
        std::vector<String> getMenu();
        int index();
    private:
        int selectedItem = -1;
        int item = 0;
        std::vector<MenuItem *> items = {
            new BoolMenuItem("item 1"),
            new BoolMenuItem("item 2"),
            new BoolMenuItem("item 3"),
            new FloatMenuItem("float 1", 10.0, 1.0),
            new FloatMenuItem("float 2", 120.0, 0.4),
            new FloatMenuItem("float 3", 0.0, 0.1)
        };
};

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
    if(selectedItem == item) {
        selectedItem = -1;
        return;
    }
    selectedItem = item;
}

void Menu::reset(){
    if(selectedItem == item){
        items[selectedItem]->reset();
        return;
    }
    selectedItem = -1;
    item = 0;
}